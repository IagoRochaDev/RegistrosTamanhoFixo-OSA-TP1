#include "Registro.h"
#include <cstring>
#include <string>
#include <iostream>

std::string Registro::packFixed() {
    char buffer[REG_FIXO_SIZE];
    std::memset(buffer, '\0', REG_FIXO_SIZE);

    nome.copy(buffer, MAX_NAME_SIZE);

    std::memcpy(buffer + MAX_NAME_SIZE, &idade, sizeof(int));

    return std::string(buffer, REG_FIXO_SIZE);
}

void Registro::unpackFixed(std::string buffer) {
    if (buffer.length() < REG_FIXO_SIZE) {
        std::cerr << "Erro: Buffer de unpackFixed é menor que o esperado." << std::endl;
        return;
    }

    this->nome = std::string(buffer.c_str(), MAX_NAME_SIZE);
    
    size_t firstNull = this->nome.find('\0');
    if (firstNull != std::string::npos) {
        this->nome = this->nome.substr(0, firstNull);
    }

    std::memcpy(&this->idade, buffer.c_str() + MAX_NAME_SIZE, sizeof(int));
}


std::string Registro::packWithLength() {
    std::string buffer;
    int nameLen = nome.length();
    
    // 1. Empacota tamanho do nome
    buffer.append(reinterpret_cast<char*>(&nameLen), sizeof(int));
    // 2. Empacota string do nome
    buffer.append(nome);
    // 3. Empacota idade
    buffer.append(reinterpret_cast<char*>(&idade), sizeof(int));
    
    return buffer;
}

void Registro::unpackWithLength(std::string data) {
    int nameLen = 0;
    const char* ptr = data.c_str();
    
    std::memcpy(&nameLen, ptr, sizeof(int));
    ptr += sizeof(int);
    
    this->nome = std::string(ptr, nameLen);
    ptr += nameLen;

    std::memcpy(&this->idade, ptr, sizeof(int));
}