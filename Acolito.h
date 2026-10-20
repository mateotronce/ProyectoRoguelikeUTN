#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include <string>

class Acolito : public Enemigo{

public:
    Acolito();
    void Ataque(Jugador& jugador);
};
