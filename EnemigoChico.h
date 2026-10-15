#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include <string>
class EnemigoChico : public Enemigo{

public:
    EnemigoChico();
    void Ataque(Jugador& jugador);
};
