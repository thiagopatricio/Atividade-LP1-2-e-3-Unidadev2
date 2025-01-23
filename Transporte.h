#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include "Cidade.h"

class Transporte {
private:
    std::string nome;                // Nome do transporte
    char tipo;                       // 'A' ou 'T'
    int capacidade;                  // Capacidade de passageiros
    int velocidade;                  // Velocidade em km/h
    int distanciaEntreDescansos;     // Distância entre descansos em km
    int tempoDeDescanso;             // Tempo de descanso em horas
    Cidade* localAtual;              // Cidade onde está atualmente

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade,
               int distanciaEntreDescansos, int tempoDeDescanso, Cidade* localAtual);

    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDeDescanso() const;
    Cidade* getLocalAtual() const;

    void setLocalAtual(Cidade* novaLocal);
};

#endif // TRANSPORTE_H
