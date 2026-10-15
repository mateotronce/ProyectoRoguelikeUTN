#include "Jugador.h"

/// Constructor ///
Jugador::Jugador() {
}

/// Getters ///
int Jugador::getVida() {
    return Vida;
}

int Jugador::getDanio() {
    return Danio;
}

int Jugador::getVel() {
    return Velocidad;
}

/// Setters ///
void Jugador::setVida(int _vida) {
    Vida = _vida;
}

void Jugador::setDanio(int _danio) {
    Danio = _danio;
}

void Jugador::setVel(int _vel) {
    Velocidad = _vel;
}
