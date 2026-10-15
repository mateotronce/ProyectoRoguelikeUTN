#pragma once
#include <string>
class Jugador{

private:
    std::string NombreJugador;
    int Vida = 100;
    int Danio = 10;
    int Velocidad = 5;

public:

///constructor///
    Jugador();

    /// Getters ///
    int getVida();
    int getDanio();
    int getVel();


    /// Setters ///
    void setVida(int _vida);
    void setDanio(int _danio);
    void setVel(int _vel);
};
