#ifndef VOO_H
#define VOO_H
#include <string>


class voo
{
public:
    voo(std::string codigo,std::string origem,int saida,std::string destino,int chegada):
        codigo(codigo),
        origem(origem),
        saida(saida),
        destino(destino),
        chegada(chegada)
    {};

    std::string codigo;
    std::string origem;
    int saida;
    std::string destino;
    int chegada;
    int tempoVoo();

    bool operator ==(voo &valor);
};

#endif // VOO_H
