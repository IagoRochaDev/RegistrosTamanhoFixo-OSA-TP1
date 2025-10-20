#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

const int MAX_NAME_SIZE = 100;
const int REG_FIXO_SIZE = MAX_NAME_SIZE + sizeof(int);

class Registro {
public:
    std::string nome;
    int idade;

    Registro() : nome(""), idade(0) {}
    Registro(std::string n, int i) : nome(n), idade(i) {}

    std::string packWithLength();
    void unpackWithLength(std::string data);
    std::string packFixed();
    void unpackFixed(std::string buffer);
};

#endif