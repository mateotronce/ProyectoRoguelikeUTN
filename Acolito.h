#pragma once
#include "Enemigo.h"
#include "Jugador.h"

class Acolito : public Enemigo{

public:
    Acolito(const RegistroEnemigo& datos, sf::Vector2f pos);
    void actualizar(float dt, const Jugador& jugador);
    void Ataque(Jugador& jugador);
};
