#include <iostream>
#include <fstream>
#include <vector>
#include "Arquivo.h"
#include "Registro.h"

void limparArquivo(const std::string& nomeArquivo) {
     std::ofstream outFile(nomeArquivo, std::ios::trunc | std::ios::binary);
     outFile.close();
     std::cout << "Arquivo '" << nomeArquivo << "' limpo para nova escrita.\n";
}

int main() {
    const std::string csvFile = "Nomes_Idades.csv";
    const std::string fixedFile = "dados.dat";

    std::cout << "\n--- Lendo do CSV ('" << csvFile << "') ---\n";
    Arquivo arqCSV(csvFile); 
    std::vector<Registro> registrosCSV = arqCSV.lerRegistrosCSV(); 

    if (registrosCSV.empty()) {
        std::cerr << "Nenhum registro lido do CSV. Encerrando.\n";
        return 1;
    }
    for (const auto& reg : registrosCSV) {
        std::cout << "Lido (CSV): Nome: " << reg.nome << ", Idade: " << reg.idade << std::endl;
    }

    std::cout << "\n--- Escrevendo em arquivo Fixo ('" << fixedFile << "') ---\n";
    limparArquivo(fixedFile); 
    Arquivo arqFixo(fixedFile); 
    for (const auto& reg : registrosCSV) {
        arqFixo.adicionarRegistroFixo(reg);
        std::cout << "Escrevendo (Fixo): Nome: " << reg.nome << ", Idade: " << reg.idade << std::endl;
    }

    std::cout << "\n--- Lendo do arquivo Fixo ('" << fixedFile << "') ---\n";
    std::vector<Registro> registrosFixo = arqFixo.lerRegistrosFixo(); 

    if (registrosFixo.empty()) {
        std::cerr << "Nenhum registro lido do arquivo fixo.\n";
    }
    for (const auto& reg : registrosFixo) {
        std::cout << "Lido (Fixo): Nome: '" << reg.nome << "', Idade: " << reg.idade << std::endl;
    }

    std::cout << "\nProcesso concluído.\n";
    return 0;
}