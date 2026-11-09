#include "Proyectil.h"

Proyectil::Proyectil(sf::Vector2f pos, sf::Vector2f direccion, float velocidad,
                     float alcance, int danio, bool esEnemigo)
    : m_forma(6.f), m_alcance(alcance), m_danio(danio), m_esEnemigo(esEnemigo) {
    m_forma.setOrigin({6.f, 6.f});
    m_forma.setPosition(pos);
    // amarillo los del jugador, violeta los enemigos
    m_forma.setFillColor(esEnemigo ? sf::Color(200, 80, 255) : sf::Color::Yellow);
    m_velocidad = direccion.normalized() * velocidad;
}

// mueve el proyectil y lo apaga si ya recorrio todo su alcance
void Proyectil::actualizar(float dt) {
    if (!m_activo) return;

    const sf::Vector2f paso = m_velocidad * dt;
    m_forma.move(paso);
    m_recorrido += paso.length();

    if (m_recorrido >= m_alcance)
        m_activo = false;
}

void Proyectil::desactivar() { m_activo = false; }

bool Proyectil::estaActivo() const { return m_activo; }
bool Proyectil::esEnemigo() const { return m_esEnemigo; }
int Proyectil::getDanio() const { return m_danio; }
sf::Vector2f Proyectil::getPosicion() const { return m_forma.getPosition(); }
sf::FloatRect Proyectil::getCaja() const { return m_forma.getGlobalBounds(); }

void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_forma, states);
}
