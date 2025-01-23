#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include <iostream>
#include "Transporte.h"
#include "Passageiro.h"
#include "Trajeto.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Trajeto* trajeto;            // Trajeto específico (origem, destino, tipo, distância)
    Viagem* proxima;             // Próxima viagem (conexão) caso exista
    bool emAndamento;

    // Controle de simulação
    int kmPercorridos;           // Quantos km já foram percorridos neste trajeto
    int horasDeDescansoRestantes;// Se o transporte estiver descansando
    int horasEmTransito;         // Total de horas em trânsito (para relatórios)

public:
    // Construtor simples para viagem
    Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Trajeto* trajeto);

    // Inicia a viagem (emAndamento = true)
    void iniciarViagem();

    // Avança a simulação em 'horas' horas
    void avancarHoras(int horas);

    // Relata o estado atual no console
    void relatarEstado() const;

    // Retorna se a viagem ainda está em andamento
    bool isEmAndamento() const;

    // Seta a próxima viagem (caso haja conexões)
    void setProxima(Viagem* v);
    Viagem* getProxima() const;

    // Getters relevantes
    Transporte* getTransporte() const;
    const std::vector<Passageiro*>& getPassageiros() const;
    Trajeto* getTrajeto() const;
    int getHorasEmTransito() const;
};

#endif // VIAGEM_H
