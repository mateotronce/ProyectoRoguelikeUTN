#pragma once
#include "Objeto.h"
#include <string>

// Una recompensa tiene una mejora y, en los altares, una maldicion.
class Recompensa {
private:
    int m_id;
    std::string m_nombre;
    Objeto m_mejora;
    int m_multiplicador;
    Objeto m_maldicion;
    bool m_tieneMaldicion;

public:
    Recompensa();
    Recompensa(int id, std::string nombre, Objeto mejora, int multiplicador = 1);
    Recompensa(int id, std::string nombre, Objeto mejora,
               int multiplicador, Objeto maldicion);

    int getId() const;
    std::string getNombre() const;
    bool tieneMaldicion() const;
    void aplicar(Jugador& jugador) const;
};
