#include "Guardian.h"

Guardian::Guardian(const RegistroEnemigo& datos, sf::Vector2f pos)
    : Enemigo(datos, pos, {56.f, 56.f}, sf::Color(130, 130, 130)) {
}

// Avanza lento hacia el jugador
void Guardian::actualizar(float dt, const Jugador& jugador) {

    moverHacia(jugador.getPosicion(), dt);

}

// Danio por contacto (el jugador maneja su invulnerabilidad)
void Guardian::Ataque(Jugador& jugador) {

    jugador.recibirDanio(getDanio());

}
