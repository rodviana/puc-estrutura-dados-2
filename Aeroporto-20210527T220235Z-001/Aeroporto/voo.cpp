#include "voo.h"



int voo::tempoVoo()
{
    if(chegada>saida)
        return chegada-saida;
    else
        return chegada+1440-saida;
}

bool voo::operator ==(voo &valor)
{
    return ((this->codigo==valor.codigo)&&(this->origem==valor.origem));
}
