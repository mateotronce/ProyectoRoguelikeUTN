#pragma once

struct Proyectil {

    float x = 0;
    float y = 0;

    float velocidadX = 0;
    float velocidadY = 0;

    int danio = 0;
    bool enemigo = false;

    void mover(float tiempoDeDisparo) {
        x += velocidadX * tiempoDeDisparo;
        y += velocidadY * tiempoDeDisparo;
    }
};

