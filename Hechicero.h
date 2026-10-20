#pragma once
#include "Enemigo.h"
#include "Proyectil.h"

class Hechicero : public Enemigo {
private:
    float tiempoDesdeUltimoDisparo = 0.f;

public:
    Hechicero();

    void acercarse(float& x, float& y,
                   float jugadorX, float jugadorY,
                   float tiempoDeDisparo);

    bool Ataque(float x, float y,
                float jugadorX, float jugadorY,
                float tiempoDeDisparo, Proyectil& proyectil);
};
