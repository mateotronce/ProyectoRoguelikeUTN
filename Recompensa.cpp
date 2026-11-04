#include "Recompensa.h"
#include "Jugador.h"

Recompensa::Recompensa() {
    m_id = -1;
    m_nombre = "";
    m_multiplicador = 1;
    m_tieneMaldicion = false;
}

Recompensa::Recompensa(int id, std::string nombre, Objeto mejora, int multiplicador) {
    m_id = id;
    m_nombre = nombre;
    m_mejora = mejora;
    m_multiplicador = multiplicador;
    m_tieneMaldicion = false;
}

Recompensa::Recompensa(int id, std::string nombre, Objeto mejora,
                       int multiplicador, Objeto maldicion) {
    m_id = id;
    m_nombre = nombre;
    m_mejora = mejora;
    m_multiplicador = multiplicador;
    m_maldicion = maldicion;
    m_tieneMaldicion = true;
}

int Recompensa::getId() const { return m_id; }
std::string Recompensa::getNombre() const { return m_nombre; }
bool Recompensa::tieneMaldicion() const { return m_tieneMaldicion; }

void Recompensa::aplicar(Jugador& jugador) const {
    m_mejora.aplicar(jugador, m_multiplicador);
    if (m_tieneMaldicion) {
        m_maldicion.aplicar(jugador);
    }
}
