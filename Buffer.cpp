#include "Buffer.h"
#include <iostream>
#include <cstring>

void Buffer::escreverRegistroFixo(Registro reg, std::ofstream &out) {
    std::string buffer = reg.packFixed();
    out.write(buffer.c_str(), buffer.length());
}

Registro Buffer::lerRegistroFixo(std::ifstream &in) {
    char buffer[REG_FIXO_SIZE];
    std::memset(buffer, '\0', REG_FIXO_SIZE);

    in.read(reinterpret_cast<char*>(buffer), REG_FIXO_SIZE);

    Registro reg;

    if (in.gcount() == REG_FIXO_SIZE) {
        reg.unpackFixed(std::string(buffer, REG_FIXO_SIZE));
    }
    return reg;
}

void Buffer::escreverRegistro(Registro reg, std::ofstream &out) {
    std::string buffer = reg.packWithLength();
    int bufferLen = buffer.length();

    out.write(reinterpret_cast<char*>(&bufferLen), sizeof(int));
    out.write(buffer.c_str(), bufferLen);
}

Registro Buffer::lerRegistro(std::ifstream &in) {
    int bufferLen = 0;

    in.read(reinterpret_cast<char*>(&bufferLen), sizeof(int));

    if (in.gcount() != sizeof(int)) {
        return Registro();
    }

    char* dataBuffer = new char[bufferLen];
    in.read(dataBuffer, bufferLen);

    if (in.gcount() == bufferLen) {
        std::string data(dataBuffer, bufferLen);
        delete[] dataBuffer;
        Registro reg;
        reg.unpackWithLength(data);
        return reg;
    }
    delete[] dataBuffer;
    return Registro();
}