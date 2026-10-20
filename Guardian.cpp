#include "Guardian.h"

Guardian::Guardian()
    : Enemigo(8, 2, 1) {
}


void Guardian::Ataque(Jugador& jugador) {

    jugador.setVida(jugador.getVida() - getDanio());

}

