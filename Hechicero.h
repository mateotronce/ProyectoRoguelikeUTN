#pragma once
#include <vector>
#include "Enemigo.h"
#include "Jugador.h"
#include "Proyectil.h"

class Hechicero : public Enemigo {
private:
    float tiempoDesdeUltimoDisparo = 0.f;

    static constexpr float DistanciaAtaque = 5.f;     // casilleros
    // Valores provisorios: el documento no define el disparo enemigo
    static constexpr float VelocidadProyectil = 8.f;  // casilleros por segundo
    static constexpr float AlcanceProyectil = 10.f;   // casilleros

public:
    Hechicero(const RegistroEnemigo& datos, sf::Vector2f pos);

    void actualizar(float dt, const Jugador& jugador, std::vector<Proyectil>& proyectiles);

    void acercarse(float dt, sf::Vector2f posJugador);
    bool Ataque(sf::Vector2f posJugador, std::vector<Proyectil>& proyectiles);
};
