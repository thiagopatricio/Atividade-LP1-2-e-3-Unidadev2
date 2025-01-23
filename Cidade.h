#ifndef CIDADE_H
#define CIDADE_H

#include <string>

class Cidade {
private:
    std::string nome;
    // Contador de visitas (usado em relatórios de "cidades mais visitadas")
    int contadorVisitas; 

public:
    Cidade(std::string nome);

    std::string getNome() const;

    // Manipulação do contador de visitas
    void incrementarVisitas();
    int getContadorVisitas() const;
};

#endif // CIDADE_H
