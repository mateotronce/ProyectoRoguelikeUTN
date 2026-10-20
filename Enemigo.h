#pragma once

class Enemigo {

private:
    int Vida;
    int Danio;
    int Velocidad;

public:

    Enemigo(int _vida, int _danio, int _velocidad);

    int getVida();
    int getDanio();
    int getVel();

    void setVida(int _vida);
    void setDanio(int _danio);
    void setVel(int _vel);
};
