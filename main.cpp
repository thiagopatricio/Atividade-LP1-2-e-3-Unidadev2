#include <iostream>
#include "ControladorDeTransito.h"

int main() {
    ControladorDeTransito controlador;

    // Exemplo de cadastro manual
    controlador.cadastrarCidade("São Paulo");
    controlador.cadastrarCidade("Rio de Janeiro");
    controlador.cadastrarCidade("Belo Horizonte");

    // Exemplo de trajetos terrestres
    controlador.cadastrarTrajeto("São Paulo", "Rio de Janeiro", 'T', 400);
    controlador.cadastrarTrajeto("Rio de Janeiro", "Belo Horizonte", 'T', 450);
    controlador.cadastrarTrajeto("São Paulo", "Belo Horizonte", 'T', 580);

    // Cadastra transportes
    controlador.cadastrarTransporte("Ônibus1", 'T', 50, 80, 200, 1, "São Paulo");
    controlador.cadastrarTransporte("Navio1", 'A', 100, 40, 300, 2, "Rio de Janeiro");

    // Cadastra passageiros
    controlador.cadastrarPassageiro("João", "São Paulo");
    controlador.cadastrarPassageiro("Maria", "São Paulo");
    controlador.cadastrarPassageiro("Paulo", "Rio de Janeiro");

    // Listas para debug
    controlador.listarCidades();
    controlador.listarTrajetos();

    // Inicia viagem: São Paulo -> Belo Horizonte
    // usando "Ônibus1" e levando "João" e "Maria"
    controlador.iniciarViagem("Ônibus1", {"João", "Maria"}, "São Paulo", "Belo Horizonte");

    // Avança 3 horas
    controlador.avancarHoras(3);
    controlador.relatarEstadoGeral();

    // Avança mais 3 horas
    controlador.avancarHoras(3);
    controlador.relatarEstadoGeral();

    // Relatório de viagens em andamento
    controlador.relatarViagensEmAndamento();

    // Relatório de cidades mais visitadas
    controlador.relatarCidadesMaisVisitadas();

    // Exemplo de salvamento/carregamento
    controlador.salvarDadosEmArquivo("dados.txt");
    // ...
    // controlador.carregarDadosDeArquivo("dados.txt");

    return 0;
}