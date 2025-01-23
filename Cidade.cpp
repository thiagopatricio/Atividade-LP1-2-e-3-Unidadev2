#include "Cidade.h"

Cidade::Cidade(std::string nome)
    : nome(nome), contadorVisitas(0) {}

std::string Cidade::getNome() const {
    return nome;
}

void Cidade::incrementarVisitas() {
    contadorVisitas++;
}

int Cidade::getContadorVisitas() const {
    return contadorVisitas;
}
