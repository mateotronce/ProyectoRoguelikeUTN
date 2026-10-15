#pragma once

class Enemigo {

private:
    int Vida;
    int Danio;
    int Velocidad;

public:

    Enemigo(int _vida, int _danio, int _velocidad) {
        Vida = _vida;
        Danio = _danio;
        Velocidad = _velocidad;
    }

    int getVida() { return Vida; }
    int getDanio() { return Danio; }
    int getVel() { return Velocidad; }

    void setVida(int _vida) { Vida = _vida; }
    void setDanio(int _danio) { Danio = _danio; }
    void setVel(int _vel) { Velocidad = _vel; }
};
