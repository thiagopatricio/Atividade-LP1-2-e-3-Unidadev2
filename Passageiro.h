#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "Cidade.h"

class Passageiro {
private:
    std::string nome;    // Nome do passageiro
    Cidade* localAtual;  // Localização atual do passageiro

public:
    Passageiro(std::string nome, Cidade* localAtual);

    std::string getNome() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
};

#endif // PASSAGEIRO_H

