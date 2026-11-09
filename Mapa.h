#pragma once
#include "Sala.h"
#include <vector>

class Mapa {
private:
    // Cada numero es el ID de una sala. El 0 significa espacio vacio.
    // Filas: de arriba hacia abajo. Columnas: de izquierda a derecha.
    int m_matriz[4][6] = {
        {0, 4, 0, 0, 0, 0},
        {0, 3, 0, 8, 0, 0},
        {1, 2, 5, 7, 9, 10},
        {0, 0, 6, 0, 0, 0}
    };

    // Guardamos los objetos Sala por separado de sus posiciones.
    Sala m_salas[10];
    int m_salaActual = 1;
    bool m_cargado = false;

    bool buscarPosicion(int idSala, int& fila, int& columna) const;

public:
    // CargadorDatos::armarMapa le envia los registros de Salas.dat.
    bool cargar(const std::vector<RegistroSala>& registros);
    bool estaCargado() const;

    // Devuelve el ID que hay en una casilla (0 si esta vacia o fuera del mapa).
    int getIdEnPosicion(int fila, int columna) const;

    Sala& getSalaActual();
    Sala* getSala(int idSala);
    int getNumeroSalaActual() const;

    // 0 = norte, 1 = sur, 2 = este, 3 = oeste.
    bool cambiarSala(int direccion);
    void marcarCompletada(int idSala);
};
