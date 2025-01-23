#ifndef CONTROLADORDETRANSITO_H
#define CONTROLADORDETRANSITO_H

#include <vector>
#include <string>
#include <map>
#include <limits>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;      
    std::vector<Trajeto*> trajetos;    
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens; // lista de viagens em andamento ou finalizadas

    // Busca auxiliares
    Cidade* buscarCidade(const std::string& nome) const;
    Transporte* buscarTransporte(const std::string& nome) const;
    Passageiro* buscarPassageiro(const std::string& nome) const;

    // Algoritmo de Dijkstra para encontrar o caminho de menor distância 
    // entre duas cidades (retorna lista de trajetos se possível)
    std::vector<Trajeto*> calcularMelhorTrajeto(Cidade* origem, Cidade* destino);

public:
    ~ControladorDeTransito(); // Destrutor para liberar memória

    void cadastrarCidade(const std::string& nome);
    void cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino, 
                          char tipo, int distancia);
    void cadastrarTransporte(const std::string& nome, char tipo, int capacidade, int velocidade,
                             int distancia_entre_descansos, int tempo_de_descanso, 
                             const std::string& localAtual);
    void cadastrarPassageiro(const std::string& nome, const std::string& localAtual);

    // Iniciar viagem levando em conta conexões
    void iniciarViagem(const std::string& nomeTransporte, 
                       const std::vector<std::string>& nomesPassageiros,
                       const std::string& nomeOrigem, 
                       const std::string& nomeDestino);

    // Avançar horas e atualizar todas as viagens em andamento
    void avancarHoras(int horas);

    // Relatórios
    void relatarEstadoGeral() const;
    void relatarViagensEmAndamento() const;
    void relatarCidadesMaisVisitadas() const;

    // Exemplo de persistência de dados
    void salvarDadosEmArquivo(const std::string& nomeArquivo) const;
    void carregarDadosDeArquivo(const std::string& nomeArquivo);

    // Métodos de debug/auxiliares
    void listarCidades() const;
    void listarTrajetos() const;
};

#endif // CONTROLADORDETRANSITO_H
