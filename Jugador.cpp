#include "Jugador.h"
#include <algorithm>

Jugador::Jugador(sf::Vector2f posInicial)
    : m_forma({50.f, 50.f}) {
    m_forma.setOrigin({25.f, 25.f});
    m_forma.setPosition(posInicial);
}

int Jugador::getVida() const { return m_vida; }
int Jugador::getVidaMaxima() const { return m_vidaMaxima; }
bool Jugador::tieneVidaOculta() const { return m_vidaOculta; }
int Jugador::getDanio() const { return m_danio; }
float Jugador::getVel() const { return m_velocidad; }
int Jugador::getCantidadProyectiles() const { return m_cantidadProyectiles; }
int Jugador::getAlcance() const { return m_alcance; }
float Jugador::getVelocidadProyectil() const { return m_velocidadProyectil; }
float Jugador::getCadencia() const { return m_cadencia; }
sf::Vector2f Jugador::getPosicion() const { return m_forma.getPosition(); }
sf::FloatRect Jugador::getCaja() const { return m_forma.getGlobalBounds(); }

void Jugador::setVida(int vida) { m_vida = std::clamp(vida, 0, m_vidaMaxima); }
void Jugador::setVidaMaxima(int vidaMaxima) {
    m_vidaMaxima = std::clamp(vidaMaxima, 1, 10);
    setVida(m_vida);
}
void Jugador::setVidaOculta(bool oculta) { m_vidaOculta = oculta; }
void Jugador::setDanio(int danio) { m_danio = std::clamp(danio, 1, 5); }
void Jugador::setVel(float vel) { m_velocidad = std::clamp(vel, 1.f, 6.f); }
void Jugador::setCantidadProyectiles(int cantidad) { m_cantidadProyectiles = std::clamp(cantidad, 1, 4); }
void Jugador::setAlcance(int alcance) { m_alcance = std::clamp(alcance, 1, 14); }
void Jugador::setVelocidadProyectil(float vel) { m_velocidadProyectil = std::max(1.f, vel); }
void Jugador::setCadencia(float cadencia) { m_cadencia = std::max(1.f, cadencia); }
void Jugador::setPosicion(sf::Vector2f pos) { m_forma.setPosition(pos); }

void Jugador::actualizar(float dt) {
    sf::Vector2f dir{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) dir.x += 1.f;

    if (dir != sf::Vector2f{0.f, 0.f}) {
        m_forma.move(dir.normalized() * m_velocidad * TamCasillero * dt);
    }
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_forma, states);
}

void Jugador::apuntarHacia(sf::Vector2f objetivo) {
    const sf::Vector2f d = objetivo - m_forma.getPosition();
    if (d == sf::Vector2f{0.f, 0.f}) return;
    m_direccion = d.normalized();
    m_forma.setRotation(d.angle());
}

sf::Vector2f Jugador::getDireccion() const { return m_direccion; }
