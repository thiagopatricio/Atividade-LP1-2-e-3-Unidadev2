#ifndef TRAJETO_H
#define TRAJETO_H

#include "Cidade.h"

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo;     // 'A' para aquático, 'T' para terrestre
    int distancia; // Distância em quilômetros

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);

    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};

#endif // TRAJETO_H
