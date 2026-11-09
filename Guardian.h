#pragma once
#include "Enemigo.h"
#include "Jugador.h"

class Guardian : public Enemigo {

public:
    Guardian(const RegistroEnemigo& datos, sf::Vector2f pos);
    void actualizar(float dt, const Jugador& jugador);
    void Ataque(Jugador& jugador);
};
