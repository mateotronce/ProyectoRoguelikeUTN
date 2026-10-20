#include "Hechicero.h"
#include <cmath>

/// Constructor ///
Hechicero::Hechicero()
    : Enemigo(2, 1, 1) {
}

/// Se acerca al jugador hasta quedar a 5 casilleros ///
void Hechicero::acercarse(float& x, float& y,
                         float jugadorX, float jugadorY,
                         float tiempoDeDisparo) {
    if (tiempoDeDisparo <= 0) return;

    float dx = jugadorX - x;
    float dy = jugadorY - y;
    float distancia = std::sqrt(dx * dx + dy * dy);

    if (distancia <= 5.f) return;

    float movimiento = getVel() * tiempoDeDisparo;
    if (movimiento > distancia - 5.f) {
        movimiento = distancia - 5.f;
    }

    x += (dx / distancia) * movimiento;
    y += (dy / distancia) * movimiento;
}

/// Dispara cada 2 segundos cuando esta a 5 casilleros o menos ///
bool Hechicero::Ataque(float x, float y,
                      float jugadorX, float jugadorY,
                      float tiempoDeDisparo, Proyectil& proyectil) {
    if (tiempoDeDisparo > 0) {
        tiempoDesdeUltimoDisparo += tiempoDeDisparo;
    }

    float dx = jugadorX - x;
    float dy = jugadorY - y;
    float distancia = std::sqrt(dx * dx + dy * dy);

    if (distancia == 0.f || distancia > 5.f || tiempoDesdeUltimoDisparo < 2.f) {
        return false;
    }

    // Valor provisorio: el documento no define la velocidad del disparo enemigo.
    const float velocidadProyectil = 8.f;

    proyectil.x = x;
    proyectil.y = y;
    proyectil.velocidadX = (dx / distancia) * velocidadProyectil;
    proyectil.velocidadY = (dy / distancia) * velocidadProyectil;
    proyectil.danio = getDanio();
    proyectil.enemigo = true;

    tiempoDesdeUltimoDisparo = 0.f;
    return true;
}
