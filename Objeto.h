#pragma once
#include <string>
#include "Jugador.h"

// Un objeto modifica una o dos estadisticas del jugador.
// Un valor positivo suma y uno negativo resta.
class Objeto {
private:
    int m_id;
    std::string m_nombre;
    bool m_esMaldicion;
    int m_atributo1;
    int m_valor1;
    int m_atributo2;
    int m_valor2;

    void aplicarEfecto(Jugador& jugador, int atributo, int valor) const;

public:
    Objeto();
    Objeto(int id, std::string nombre, bool esMaldicion,
           int atributo1, int valor1, int atributo2 = 0, int valor2 = 0);

    int getId() const;
    std::string getNombre() const;
    bool esMaldicion() const;

    void aplicar(Jugador& jugador, int veces = 1) const;
};
