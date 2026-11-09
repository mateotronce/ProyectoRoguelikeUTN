#include "Recompensa.h"
#include "Jugador.h"

Recompensa::Recompensa() {
    m_id = -1;
    m_nombre = "";
    m_multiplicador = 1;
    m_tieneMaldicion = false;
    prepararForma();
}

Recompensa::Recompensa(int id, std::string nombre, Objeto mejora, int multiplicador) {
    m_id = id;
    m_nombre = nombre;
    m_mejora = mejora;
    m_multiplicador = multiplicador;
    m_tieneMaldicion = false;
    prepararForma();
}

Recompensa::Recompensa(int id, std::string nombre, Objeto mejora,
                       int multiplicador, Objeto maldicion) {
    m_id = id;
    m_nombre = nombre;
    m_mejora = mejora;
    m_multiplicador = multiplicador;
    m_maldicion = maldicion;
    m_tieneMaldicion = true;
    prepararForma();
}

// Dorado las mejoras, violeta las reliquias malditas (con pedestal)
void Recompensa::prepararForma() {
    m_forma.setRadius(14.f);
    m_forma.setOrigin({14.f, 14.f});
    m_forma.setFillColor(m_tieneMaldicion ? sf::Color(150, 60, 190) : sf::Color(230, 190, 50));

    m_pedestal.setSize({48.f, 48.f});
    m_pedestal.setOrigin({24.f, 24.f});
    m_pedestal.setFillColor(sf::Color(100, 95, 90));
}

int Recompensa::getId() const { return m_id; }
std::string Recompensa::getNombre() const { return m_nombre; }
bool Recompensa::tieneMaldicion() const { return m_tieneMaldicion; }

std::string Recompensa::getDescripcion() const {
    std::string texto = m_nombre;
    if (m_tieneMaldicion) {
        texto += "\n+ " + m_mejora.getNombre() + " x" + std::to_string(m_multiplicador);
        texto += "\n- " + m_maldicion.getNombre();
    }
    return texto;
}

void Recompensa::aplicar(Jugador& jugador) const {
    m_mejora.aplicar(jugador, m_multiplicador);
    if (m_tieneMaldicion) {
        m_maldicion.aplicar(jugador);
    }
}

void Recompensa::setPosicion(sf::Vector2f pos) {
    m_forma.setPosition(pos);
    m_pedestal.setPosition(pos);
}
sf::Vector2f Recompensa::getPosicion() const { return m_forma.getPosition(); }
sf::FloatRect Recompensa::getCaja() const { return m_forma.getGlobalBounds(); }

void Recompensa::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (m_tieneMaldicion)
        target.draw(m_pedestal, states);
    target.draw(m_forma, states);
}
