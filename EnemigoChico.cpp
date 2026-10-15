#include "EnemigoChico.h"

/// Constructor ///
EnemigoChico::EnemigoChico() : Enemigo(30, 5, 2) {
}

/// Ataque cuerpo a cuerpo ///
void EnemigoChico::Ataque(Jugador& jugador) {

    int vidaActual = jugador.getVida();
    int danioEnemigo = getDanio();

    int vidaRestante = vidaActual - danioEnemigo;

    if (vidaRestante < 0) {
        vidaRestante = 0;
    }

    jugador.setVida(vidaRestante);
}

