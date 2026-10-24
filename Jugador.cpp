#include "Jugador.h"
#include <algorithm>   // std::clamp

Jugador::Jugador(sf::Vector2f posInicial)
    : m_forma({50.f, 50.f})
{
    m_forma.setOrigin({25.f, 25.f});
    m_forma.setPosition(posInicial);
}

/// Getters ///
int   Jugador::getVida() const                { return m_vida; }
int   Jugador::getDanio() const               { return m_danio; }
float Jugador::getVel() const                 { return m_velocidad; }
int   Jugador::getCantidadProyectiles() const { return m_cantidadProyectiles; }
int   Jugador::getAlcance() const             { return m_alcance; }
float Jugador::getVelocidadProyectil() const  { return m_velocidadProyectil; }
float Jugador::getCadencia() const            { return m_cadencia; }

sf::Vector2f  Jugador::getPosicion() const { return m_forma.getPosition(); }
sf::FloatRect Jugador::getCaja() const     { return m_forma.getGlobalBounds(); }

/// Setters ///
void Jugador::setVida(int vida)                     { m_vida = std::clamp(vida, 0, VidaMaxima); }
void Jugador::setDanio(int danio)                   { m_danio = danio; }
void Jugador::setVel(float vel)                     { m_velocidad = vel; }
void Jugador::setCantidadProyectiles(int cantidad)  { m_cantidadProyectiles = cantidad; }
void Jugador::setAlcance(int alcance)               { m_alcance = alcance; }
void Jugador::setVelocidadProyectil(float vel)      { m_velocidadProyectil = vel; }
void Jugador::setCadencia(float cadencia)           { m_cadencia = cadencia; }
void Jugador::setPosicion(sf::Vector2f pos)         { m_forma.setPosition(pos); }

/// Movimiento ///
void Jugador::actualizar(float dt)
{
    sf::Vector2f dir{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) dir.x += 1.f;

    if (dir != sf::Vector2f{0.f, 0.f})
        m_forma.move(dir.normalized() * m_velocidad * dt);   // velocidad DESPUÉS de normalizar
}

/// Dibujo ///
void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_forma, states);
}


void Jugador::apuntarHacia(sf::Vector2f objetivo)
{
    const sf::Vector2f d = objetivo - m_forma.getPosition();
    if (d == sf::Vector2f{0.f, 0.f})
        return;   // mouse justo encima: no hay dirección

    m_direccion = d.normalized();
    m_forma.setRotation(d.angle());
}

sf::Vector2f Jugador::getDireccion() const { return m_direccion; }
