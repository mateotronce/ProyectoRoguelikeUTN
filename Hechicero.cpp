#include "Hechicero.h"
#include "Constantes.h"

/// Constructor ///
Hechicero::Hechicero(const RegistroEnemigo& datos, sf::Vector2f pos)
    : Enemigo(datos, pos, {32.f, 32.f}, sf::Color(120, 60, 200)) {
}

/// Se acerca y dispara en cada frame ///
void Hechicero::actualizar(float dt, const Jugador& jugador, std::vector<Proyectil>& proyectiles) {
    tiempoDesdeUltimoDisparo += dt;

    acercarse(dt, jugador.getPosicion());
    Ataque(jugador.getPosicion(), proyectiles);
}

/// Se acerca al jugador hasta quedar a 5 casilleros ///
void Hechicero::acercarse(float dt, sf::Vector2f posJugador) {
    moverHacia(posJugador, dt, DistanciaAtaque * TamCasillero);
}

/// Dispara segun su cadencia cuando esta a 5 casilleros o menos ///
bool Hechicero::Ataque(sf::Vector2f posJugador, std::vector<Proyectil>& proyectiles) {
    const sf::Vector2f d = posJugador - getPosicion();
    const float distancia = d.length();

    // Pequeño margen para que no deje de disparar por redondeo
    if (distancia == 0.f || distancia > DistanciaAtaque * TamCasillero + 1.f)
        return false;
    if (tiempoDesdeUltimoDisparo * 1000.f < getCadenciaDisparo())
        return false;

    // Apunta a donde esta el jugador en este instante
    proyectiles.emplace_back(getPosicion(), d, VelocidadProyectil * TamCasillero,
                             AlcanceProyectil * TamCasillero, getDanio(), true);

    tiempoDesdeUltimoDisparo = 0.f;
    return true;
}
