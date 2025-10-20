#include "Arquivo.h"
#include "Buffer.h" 
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<Registro> Arquivo::lerRegistrosCSV() {
    std::vector<Registro> registros;
    std::ifstream inFile(nomeDoArquivo);

    if (!inFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo CSV: " << nomeDoArquivo << std::endl;
        return registros;
    }

    std::string line, nome, idadeStr;

    if (!std::getline(inFile, line)) {
        std::cerr << "Arquivo CSV vazio ou erro ao ler cabeçalho." << std::endl;
        inFile.close();
        return registros;
    }
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        
        // "separados por vírgulas"
        std::getline(ss, nome, ',');
        std::getline(ss, idadeStr, ',');
        try {
            int idade = std::stoi(idadeStr);
            registros.push_back(Registro(nome, idade));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erro ao converter idade: '" << idadeStr << "' na linha: " << line << std::endl;
        } catch (const std::out_of_range& e) {
             std::cerr << "Erro (out_of_range) ao converter idade: '" << idadeStr << "'" << std::endl;
        }
    }
    inFile.close();
    return registros;
}

void Arquivo::adicionarRegistroFixo(Registro reg) {

    std::ofstream outFile(nomeDoArquivo, std::ios::binary | std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo para escrita fixa: " << nomeDoArquivo << std::endl;
        return;
    }

    Buffer buffer;
    buffer.escreverRegistroFixo(reg, outFile);
    outFile.close();
}
std::vector<Registro> Arquivo::lerRegistrosFixo() {
    std::vector<Registro> registros;
    

    std::ifstream inFile(nomeDoArquivo, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo para leitura fixa: " << nomeDoArquivo << std::endl;
        return registros;
    }

    Buffer buffer;
    while (true) {
        Registro reg = buffer.lerRegistroFixo(inFile);
        if (inFile.fail() || inFile.eof()) {
            break;
        }
        
        registros.push_back(reg);
    }

    inFile.close();
    return registros;
}