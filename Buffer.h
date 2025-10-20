#ifndef BUFFER_H
#define BUFFER_H

#include <fstream>
#include "Registro.h"

class Buffer {
public:
    void escreverRegistro(Registro reg, std::ofstream &out);
    Registro lerRegistro(std::ifstream &in);
    void escreverRegistroFixo(Registro reg, std::ofstream &out);
    Registro lerRegistroFixo(std::ifstream &in);
};

#endif