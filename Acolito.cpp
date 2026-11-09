#include "Acolito.h"


Acolito::Acolito(const RegistroEnemigo& datos, sf::Vector2f pos)
    :Enemigo(datos, pos, {36.f, 36.f}, sf::Color(200, 50, 50))
{
}

// Persigue al jugador en linea recta
void Acolito::actualizar(float dt, const Jugador& jugador)
{

    moverHacia(jugador.getPosicion(), dt);

}

// Danio por contacto (el jugador maneja su invulnerabilidad)
void Acolito::Ataque(Jugador& jugador)
{

    jugador.recibirDanio(getDanio());

}
