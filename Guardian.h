#pragma once
#include "Enemigo.h"
#include "Jugador.h"

class Guardian : public Enemigo {

public:
    Guardian();
    void Ataque(Jugador& jugador);
};
