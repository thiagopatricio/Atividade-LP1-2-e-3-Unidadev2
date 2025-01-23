#include <algorithm>
#include "ControladorDeTransito.h"
#include <iostream>
#include <queue>
#include <fstream>

// --------------
// Construtor/Destrutor
// --------------
ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades)     delete c;
    for (auto t : trajetos)    delete t;
    for (auto tr : transportes)delete tr;
    for (auto p : passageiros) delete p;
    for (auto v : viagens)     delete v;
}

// --------------
// Métodos Auxiliares de Busca
// --------------
Cidade* ControladorDeTransito::buscarCidade(const std::string& nome) const {
    for (auto c : cidades) {
        if (c->getNome() == nome) return c;
    }
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(const std::string& nome) const {
    for (auto t : transportes) {
        if (t->getNome() == nome) return t;
    }
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(const std::string& nome) const {
    for (auto p : passageiros) {
        if (p->getNome() == nome) return p;
    }
    return nullptr;
}

// --------------
// Cadastro de Cidade
// --------------
void ControladorDeTransito::cadastrarCidade(const std::string& nome) {
    if (buscarCidade(nome)) {
        std::cout << "Cidade '" << nome << "' já cadastrada.\n";
        return;
    }
    cidades.push_back(new Cidade(nome));
    std::cout << "Cidade '" << nome << "' cadastrada com sucesso!\n";
}

// --------------
// Cadastro de Trajeto
// --------------
void ControladorDeTransito::cadastrarTrajeto(const std::string& nomeOrigem, 
                                             const std::string& nomeDestino, 
                                             char tipo, 
                                             int distancia) {
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);
    if (!origem || !destino) {
        std::cout << "Cidades inválidas para o trajeto.\n";
        return;
    }
    // Cria novo trajeto
    trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
    std::cout << "Trajeto cadastrado: " << nomeOrigem 
              << " -> " << nomeDestino 
              << ", tipo=" << tipo 
              << ", dist=" << distancia << "\n";
}

// --------------
// Cadastro de Transporte
// --------------
void ControladorDeTransito::cadastrarTransporte(const std::string& nome, 
                                                char tipo, 
                                                int capacidade, 
                                                int velocidade,
                                                int distancia_entre_descansos, 
                                                int tempo_de_descanso, 
                                                const std::string& localAtual) {
    if (buscarTransporte(nome)) {
        std::cout << "Transporte '" << nome << "' já cadastrado.\n";
        return;
    }
    Cidade* cid = buscarCidade(localAtual);
    if (!cid) {
        std::cout << "Cidade de localização inválida.\n";
        return;
    }
    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade,
                                         distancia_entre_descansos, tempo_de_descanso, cid));
    std::cout << "Transporte '" << nome << "' cadastrado com sucesso!\n";
}

// --------------
// Cadastro de Passageiro
// --------------
void ControladorDeTransito::cadastrarPassageiro(const std::string& nome, 
                                                const std::string& localAtual) {
    if (buscarPassageiro(nome)) {
        std::cout << "Passageiro '" << nome << "' já cadastrado.\n";
        return;
    }
    Cidade* cid = buscarCidade(localAtual);
    if (!cid) {
        std::cout << "Cidade inválida para localAtual.\n";
        return;
    }
    passageiros.push_back(new Passageiro(nome, cid));
    std::cout << "Passageiro '" << nome << "' cadastrado com sucesso!\n";
}

// --------------
// Calcular Melhor Trajeto (Dijkstra Simplificado)
// Retorna lista de Trajetos (cada aresta) que compõem o caminho mínimo.
// --------------
std::vector<Trajeto*> ControladorDeTransito::calcularMelhorTrajeto(Cidade* origem, Cidade* destino) {
    // Montar um grafo baseado na lista de trajetos
    // Usaremos um map< Cidade*, vector< pair<Cidade*, Trajeto*> > >
    std::map<Cidade*, std::vector<Trajeto*>> adj;
    for (auto t : trajetos) {
        // Armazenando na adjacency list
        adj[t->getOrigem()].push_back(t);
    }

    // Dijkstra
    std::map<Cidade*, int> dist;    // distância acumulada
    std::map<Cidade*, Cidade*> pai; // anterior no caminho
    for (auto c : cidades) {
        dist[c] = std::numeric_limits<int>::max();
        pai[c] = nullptr;
    }

    // Cidade de origem tem distância 0
    dist[origem] = 0;

    // Usaremos uma fila de prioridade (min-heap)
    // Mas aqui simplificamos usando std::queue ou algo similar
    // Para usar dijkstra de modo correto, use std::priority_queue custom.
    struct Par {
        Cidade* c;
        int d;
        bool operator>(const Par& o) const { return d > o.d; }
    };
    std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;
    pq.push({origem, 0});

    while (!pq.empty()) {
        Par top = pq.top(); 
        pq.pop();

        Cidade* u = top.c;
        int d_u = top.d;
        if (d_u > dist[u]) continue; // Se não é mais atual, ignore

        if (u == destino) break; // Já encontramos o melhor caminho

        // Explora adjacências
        for (auto t : adj[u]) {
            Cidade* v = t->getDestino();
            int custo = t->getDistancia();
            if (dist[u] + custo < dist[v]) {
                dist[v] = dist[u] + custo;
                pai[v] = u;
                // Empilha na fila
                pq.push({v, dist[v]});
            }
        }
    }

    // Se não encontramos caminho, dist[destino] será infinito
    if (dist[destino] == std::numeric_limits<int>::max()) {
        return {}; // caminho vazio
    }

    // Reconstruir o caminho de cidades
    // Precisamos remontar a lista de "Trajeto*" correspondente
    // para cada passo (pai[v], v).
    std::vector<Cidade*> caminhoCidades;
    for(Cidade* at = destino; at != nullptr; at = pai[at]) {
        caminhoCidades.push_back(at);
    }
    std::reverse(caminhoCidades.begin(), caminhoCidades.end());

    // Montar lista de Trajetos
    std::vector<Trajeto*> caminhoTrajetos;
    for (size_t i = 0; i < caminhoCidades.size() - 1; i++) {
        Cidade* cOrig = caminhoCidades[i];
        Cidade* cDest = caminhoCidades[i+1];
        // Acha o trajeto exato que liga cOrig->cDest
        for (auto t : adj[cOrig]) {
            if (t->getDestino() == cDest) {
                caminhoTrajetos.push_back(t);
                break;
            }
        }
    }
    return caminhoTrajetos;
}

// --------------
// Iniciar viagem
// --------------
void ControladorDeTransito::iniciarViagem(const std::string& nomeTransporte, 
                                          const std::vector<std::string>& nomesPassageiros,
                                          const std::string& nomeOrigem, 
                                          const std::string& nomeDestino) {
    Transporte* trans = buscarTransporte(nomeTransporte);
    if (!trans) {
        std::cout << "Transporte nao encontrado: " << nomeTransporte << "\n";
        return;
    }
    Cidade* orig = buscarCidade(nomeOrigem);
    Cidade* dest = buscarCidade(nomeDestino);
    if (!orig || !dest) {
        std::cout << "Origem ou destino invalidos.\n";
        return;
    }
    // Verifica se o transporte está na cidade de origem
    if (trans->getLocalAtual() != orig) {
        std::cout << "Transporte nao esta na cidade de origem especificada.\n";
        return;
    }

    // Coletar ponteiros de passageiros
    std::vector<Passageiro*> listaPassageiros;
    for (auto& nomeP : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nomeP);
        if (!p) {
            std::cout << "Passageiro '" << nomeP << "' nao encontrado.\n";
            return;
        }
        if (p->getLocalAtual() != orig) {
            std::cout << "Passageiro '" << nomeP << "' nao esta na cidade de origem.\n";
            return;
        }
        listaPassageiros.push_back(p);
    }

    // Verifica capacidade do transporte
    if ((int)listaPassageiros.size() > trans->getCapacidade()) {
        std::cout << "Capacidade do transporte excedida.\n";
        return;
    }

    // Calcular melhor trajeto (pode ser direto ou com conexoes)
    std::vector<Trajeto*> caminho = calcularMelhorTrajeto(orig, dest);
    if (caminho.empty()) {
        std::cout << "Nao existe trajeto (direto ou com conexoes) entre "
                  << nomeOrigem << " e " << nomeDestino << "\n";
        return;
    }

    // Criar uma cadeia de Viagens
    Viagem* viagemAnterior = nullptr;
    for (size_t i = 0; i < caminho.size(); i++) {
        Viagem* nova = new Viagem(trans, listaPassageiros, caminho[i]);
        viagens.push_back(nova);
        if (viagemAnterior) {
            viagemAnterior->setProxima(nova);
        }
        viagemAnterior = nova;
    }

    // Iniciar a primeira viagem da cadeia
    viagens.back()->getTrajeto()->getDestino()->incrementarVisitas(); 
    // (opcional: se quiser contar a origem)

    Viagem* primeira = viagens[viagens.size() - caminho.size()];
    primeira->iniciarViagem();
    std::cout << "Viagem iniciada de " << nomeOrigem << " para " << nomeDestino << "!\n";
}

// --------------
// Avançar Horas
// --------------
void ControladorDeTransito::avancarHoras(int horas) {
    if (horas <= 0) {
        std::cout << "Horas deve ser > 0.\n";
        return;
    }
    // Avançar cada viagem em andamento
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            v->avancarHoras(horas);
        }
        // Se ela terminar e tiver próxima, a próxima inicia dentro do próprio `avancarHoras`
        // (já previsto em Viagem.cpp)
    }
    std::cout << "Avanco de " << horas << " horas concluido.\n";
}

// --------------
// Relatórios
// --------------
void ControladorDeTransito::relatarEstadoGeral() const {
    std::cout << "\n----- RELATORIO GERAL -----\n";

    // 1) Onde está cada pessoa
    std::cout << "\nPassageiros:\n";
    for (auto p : passageiros) {
        std::cout << " - " << p->getNome() << " esta em " << p->getLocalAtual()->getNome() << "\n";
    }

    // 2) Onde está cada transporte
    std::cout << "\nTransportes:\n";
    for (auto t : transportes) {
        std::cout << " - " << t->getNome() << " esta em " << t->getLocalAtual()->getNome() << "\n";
    }

    // 3) Relatar viagens (todas)
    std::cout << "\nViagens (em andamento ou concluidas):\n";
    for (auto v : viagens) {
        v->relatarEstado();
    }
    std::cout << "------------------------------\n\n";
}

void ControladorDeTransito::relatarViagensEmAndamento() const {
    std::cout << "\n----- VIAGENS EM ANDAMENTO -----\n";
    for (auto v : viagens) {
        if (v->isEmAndamento()) {
            v->relatarEstado();
        }
    }
    std::cout << "--------------------------------\n\n";
}

void ControladorDeTransito::relatarCidadesMaisVisitadas() const {
    std::cout << "\n----- CIDADES MAIS VISITADAS -----\n";
    // Ordenar cidades por contador de visitas
    std::vector<Cidade*> copia = cidades;
    std::sort(copia.begin(), copia.end(), 
        [](Cidade* a, Cidade* b){
            return a->getContadorVisitas() > b->getContadorVisitas();
        }
    );
    for (auto c : copia) {
        std::cout << c->getNome() << " - visitas: " << c->getContadorVisitas() << "\n";
    }
    std::cout << "----------------------------------\n\n";
}

// --------------
// Persistência de Dados (Exemplo Simples)
// --------------
void ControladorDeTransito::salvarDadosEmArquivo(const std::string& nomeArquivo) const {
    std::ofstream out(nomeArquivo);
    if (!out.is_open()) {
        std::cout << "Erro ao abrir arquivo para escrita.\n";
        return;
    }
    // Exemplo: salvar apenas cidades e trajetos
    // Você pode expandir para salvar todos os dados que desejar
    out << cidades.size() << "\n";
    for (auto c : cidades) {
        out << c->getNome() << " " << c->getContadorVisitas() << "\n";
    }
    out << trajetos.size() << "\n";
    for (auto t : trajetos) {
        out << t->getOrigem()->getNome() << " "
            << t->getDestino()->getNome() << " "
            << t->getTipo() << " "
            << t->getDistancia() << "\n";
    }
    out.close();
    std::cout << "Dados salvos em " << nomeArquivo << "\n";
}

void ControladorDeTransito::carregarDadosDeArquivo(const std::string& nomeArquivo) {
    std::ifstream in(nomeArquivo);
    if (!in.is_open()) {
        std::cout << "Erro ao abrir arquivo para leitura.\n";
        return;
    }
    // Limpa dados atuais
    for (auto c : cidades)     delete c;
    for (auto t : trajetos)    delete t;
    cidades.clear();
    trajetos.clear();

    size_t nCidades;
    in >> nCidades;
    for (size_t i = 0; i < nCidades; i++) {
        std::string nome;
        int visitas;
        in >> nome >> visitas;
        Cidade* c = new Cidade(nome);
        // "hack": incrementamos manualmente as visitas
        for(int v = 0; v < visitas; v++) {
            c->incrementarVisitas();
        }
        cidades.push_back(c);
    }
    size_t nTrajetos;
    in >> nTrajetos;
    for (size_t i = 0; i < nTrajetos; i++) {
        std::string orig, dest;
        char tipo;
        int dist;
        in >> orig >> dest >> tipo >> dist;
        Cidade* cOrig = buscarCidade(orig);
        Cidade* cDest = buscarCidade(dest);
        if (cOrig && cDest) {
            trajetos.push_back(new Trajeto(cOrig, cDest, tipo, dist));
        }
    }
    in.close();
    std::cout << "Dados carregados de " << nomeArquivo << "\n";
}

// --------------
// Métodos de Debug/Auxiliares
// --------------
void ControladorDeTransito::listarCidades() const {
    std::cout << "\nLista de Cidades:\n";
    for (auto c : cidades) {
        std::cout << " - " << c->getNome() << " (visitas: " << c->getContadorVisitas() << ")\n";
    }
    std::cout << "\n";
}

void ControladorDeTransito::listarTrajetos() const {
    std::cout << "\nLista de Trajetos:\n";
    for (auto t : trajetos) {
        std::cout << " - " << t->getOrigem()->getNome() 
                  << " -> " << t->getDestino()->getNome()
                  << " [" << t->getTipo() << "] dist: " << t->getDistancia() << "\n";
    }
    std::cout << "\n";
}