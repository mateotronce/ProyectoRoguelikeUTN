#include "Enemigo.h"
#include "Acolito.h"
#include <string>

Acolito::Acolito()
    :Enemigo(4, 1, 2)
{
}

void Acolito::Ataque(Jugador& jugador)
{

    jugador.setVida(jugador.getVida() - getDanio());

}

