#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include <vector>
#include "Registro.h"

/**
 * @brief Classe para representar o arquivo
 */
class Arquivo {
public:
    std::string nomeDoArquivo;

    Arquivo(std::string nome) : nomeDoArquivo(nome) {}

    std::vector<Registro> lerRegistrosCSV();

    void adicionarRegistroFixo(Registro reg);

    std::vector<Registro> lerRegistrosFixo();
};

#endif