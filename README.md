# Sistema Controlador de Viagens

Este projeto em C++ implementa um **Sistema de Controle de Viagens** entre cidades, com foco em **programação orientada a objetos**.  
Ele permite **cadastrar cidades**, **trajetos**, **transportes** e **passageiros**,  
além de **simular viagens** (com uma ou mais conexões) e gerar **relatórios**.

---

## Índice

- [Funcionalidades Principais](#funcionalidades-principais)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Compilar e Executar](#como-compilar-e-executar)
- [Exemplo de Uso](#exemplo-de-uso)
- [Possíveis Extensões](#possíveis-extensões)
- [Licença](#licença)

---

## Funcionalidades Principais

1. **Cadastro de Cidades**  
   - Inclui nome e um contador de visitas (para estatísticas de cidades mais procuradas).

2. **Cadastro de Trajetos**  
   - Associar uma cidade de origem a outra de destino, informando:  
     - Tipo de trajeto (`'T'` para terrestre ou `'A'` para aquático).  
     - Distância em quilômetros.

3. **Cadastro de Transportes**  
   - Nome,  
   - Tipo (`'T'` ou `'A'`),  
   - Capacidade de passageiros,  
   - Velocidade (km/h),  
   - Distância entre descansos (km),  
   - Tempo de descanso (horas),  
   - Cidade inicial (localização atual).

4. **Cadastro de Passageiros**  
   - Nome,  
   - Cidade onde o passageiro se encontra atualmente.

5. **Gestão de Viagens**  
   - Iniciar viagens informando:
     - Transporte a ser utilizado,  
     - Lista de passageiros,  
     - Cidade de origem e destino.  
   - Calcular o **melhor caminho** (via **Dijkstra** simples) para percorrer o trajeto desejado (com possíveis conexões).  
   - Avançar horas para simular a viagem:
     - Cálculo de distância percorrida.  
     - Verificação de paradas de descanso e tempo de descanso.  
     - Registro de chegada ao destino e cidades visitadas.

6. **Relatórios**  
   - Onde estão cada passageiro e transporte (em cidade ou em trânsito).  
   - Quais viagens estão em andamento ou concluídas.  
   - Cidades mais visitadas.

7. **Persistência de Dados (Básica)**  
   - Métodos para salvar e carregar dados em arquivos texto.  
   - Fácil de expandir para salvar/carregar toda a estrutura do sistema.

---

## Estrutura do Projeto


### Classes

1. **Cidade**: Nome da cidade e um contador de visitas (para relatórios de popularidade).  
2. **Trajeto**: Ligação entre duas cidades, com tipo (`'T'` ou `'A'`) e distância.  
3. **Transporte**: Informações sobre capacidade, velocidade, paradas de descanso e cidade atual.  
4. **Passageiro**: Nome e localização atual.  
5. **Viagem**: Gerencia a simulação do transporte em um trajeto específico (ou em conexões).  
6. **ControladorDeTransito**: Classe-fachada que agrega todas as entidades e gerencia suas interações (cadastro, busca, viagens, relatórios, persistência etc.).

---

## Como Compilar e Executar

1. **Compilação via linha de comando (g++)**

   ```bash
   g++ main.cpp \
       Cidade.cpp \
       Trajeto.cpp \
       Transporte.cpp \
       Passageiro.cpp \
       Viagem.cpp \
       ControladorDeTransito.cpp \
       -o sistema_viagens

Observação: certifique-se de incluir -std=c++11 ou superior, se precisar de recursos mais recentes.

Em seguida, rode:

bash
Copiar
./sistema_viagens
Compilação via CMake

Crie um arquivo CMakeLists.txt que liste todos os .cpp e gere o executável.
Execute cmake . e depois make, resultando em um binário executável.
Importante:

Em ControladorDeTransito.cpp (ou onde se use std::reverse e std::sort), lembre-se de incluir o cabeçalho <algorithm> para evitar erros de compilação.

Exemplo de Uso
main.cpp (exemplo simplificado)

#include <iostream>
#include "ControladorDeTransito.h"

int main() {
    ControladorDeTransito controlador;

    // Cadastro de cidades
    controlador.cadastrarCidade("São Paulo");
    controlador.cadastrarCidade("Rio de Janeiro");
    controlador.cadastrarCidade("Belo Horizonte");

    // Cadastro de trajetos
    controlador.cadastrarTrajeto("São Paulo", "Rio de Janeiro", 'T', 400);
    controlador.cadastrarTrajeto("Rio de Janeiro", "Belo Horizonte", 'T', 450);
    controlador.cadastrarTrajeto("São Paulo", "Belo Horizonte", 'T', 580);

    // Cadastro de transportes
    controlador.cadastrarTransporte("Ônibus1", 'T', 50, 80, 200, 1, "São Paulo");
    controlador.cadastrarTransporte("Navio1", 'A', 100, 40, 300, 2, "Rio de Janeiro");

    // Cadastro de passageiros
    controlador.cadastrarPassageiro("João", "São Paulo");
    controlador.cadastrarPassageiro("Maria", "São Paulo");
    controlador.cadastrarPassageiro("Paulo", "Rio de Janeiro");

    // Inicia viagem de São Paulo -> Belo Horizonte
    controlador.iniciarViagem("Ônibus1", {"João", "Maria"}, "São Paulo", "Belo Horizonte");

    // Avança 3 horas na simulação
    controlador.avancarHoras(3);
    controlador.relatarEstadoGeral();

    // Avança mais 3 horas
    controlador.avancarHoras(3);
    controlador.relatarEstadoGeral();

    // Relatórios adicionais
    controlador.relatarViagensEmAndamento();
    controlador.relatarCidadesMaisVisitadas();

    // Exemplo de salvamento de dados
    controlador.salvarDadosEmArquivo("dados.txt");

    return 0;
}
Fluxo Resumido
Cadastrar cidades, trajetos, transportes e passageiros.
Iniciar uma viagem, informando:
Qual transporte usar,
Quais passageiros vão embarcar,
Cidade de origem e destino.
Avançar horas para simular a viagem.
Consultar relatórios sobre o estado do sistema (passageiros, transportes, viagens, etc.).
