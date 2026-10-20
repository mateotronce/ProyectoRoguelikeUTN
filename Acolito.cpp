#include "Acolito.h"


Acolito::Acolito()
    :Enemigo(4, 1, 2)
{
}

void Acolito::Ataque(Jugador& jugador)
{

    jugador.setVida(jugador.getVida() - getDanio());

}

