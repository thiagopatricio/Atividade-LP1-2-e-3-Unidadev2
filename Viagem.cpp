#include "Viagem.h"

Viagem::Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Trajeto* trajeto)
    : transporte(transporte), passageiros(passageiros), trajeto(trajeto), 
      proxima(nullptr), emAndamento(false), kmPercorridos(0),
      horasDeDescansoRestantes(0), horasEmTransito(0) {}

void Viagem::iniciarViagem() {
    emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento || horas <= 0) return;

    int velocidade = transporte->getVelocidade();
    int distEntreDescansos = transporte->getDistanciaEntreDescansos();
    int tempoDeDescanso = transporte->getTempoDeDescanso();
    int distanciaTotal = trajeto->getDistancia();

    for(int i = 0; i < horas; i++) {
        if (!emAndamento) break; // Caso finalize no meio do loop

        // Se ainda estamos descansando
        if (horasDeDescansoRestantes > 0) {
            horasDeDescansoRestantes--;
            horasEmTransito++;
            continue;
        }

        // Estamos viajando
        kmPercorridos += velocidade; 
        horasEmTransito++;

        // Se chegamos ou passamos a distância total do trajeto
        if (kmPercorridos >= distanciaTotal) {
            // Finaliza a viagem atual
            emAndamento = false;
            kmPercorridos = distanciaTotal; // Ajuste para não passar do total

            // Ao finalizar, atualizar local do transporte e passageiros
            Cidade* destino = trajeto->getDestino();
            transporte->setLocalAtual(destino);
            for (auto p : passageiros) {
                p->setLocalAtual(destino);
            }
            // Incrementa contador de visitas na cidade de destino
            destino->incrementarVisitas();

            // Se existe uma próxima viagem em conexão, inicia a próxima
            if (proxima) {
                proxima->iniciarViagem();
            }
            break;
        }

        // Verifica se atingimos um múltiplo de distânciaEntreDescansos 
        // para efetuar descanso
        if (distEntreDescansos > 0 && (kmPercorridos % distEntreDescansos) == 0) {
            horasDeDescansoRestantes = tempoDeDescanso;
        }
    }
}

void Viagem::relatarEstado() const {
    if (emAndamento) {
        std::cout << "Viagem em andamento: "
                  << trajeto->getOrigem()->getNome() << " -> "
                  << trajeto->getDestino()->getNome() 
                  << " | Km percorridos: " << kmPercorridos
                  << "/" << trajeto->getDistancia()
                  << " | Horas em transito: " << horasEmTransito << "\n";
    } else {
        std::cout << "Viagem finalizada: "
                  << trajeto->getOrigem()->getNome() << " -> "
                  << trajeto->getDestino()->getNome() 
                  << " | Total de horas: " << horasEmTransito << "\n";
    }
}

bool Viagem::isEmAndamento() const {
    return emAndamento;
}

void Viagem::setProxima(Viagem* v) {
    proxima = v;
}

Viagem* Viagem::getProxima() const {
    return proxima;
}

Transporte* Viagem::getTransporte() const {
    return transporte;
}

const std::vector<Passageiro*>& Viagem::getPassageiros() const {
    return passageiros;
}

Trajeto* Viagem::getTrajeto() const {
    return trajeto;
}

int Viagem::getHorasEmTransito() const {
    return horasEmTransito;
}
