#include "Jugador.h"
#include <algorithm>

Jugador::Jugador(sf::Vector2f posInicial)
    : m_forma({50.f, 50.f}) {
    m_forma.setOrigin({25.f, 25.f});
    m_forma.setPosition(posInicial);
}

std::string Jugador::getNombre() const { return m_nombre; }
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

// Caja fija de 40x40: la forma rota al apuntar y su getGlobalBounds se agrandaria
sf::FloatRect Jugador::getCaja() const {
    return sf::FloatRect(m_forma.getPosition() - sf::Vector2f{20.f, 20.f}, {40.f, 40.f});
}

void Jugador::setNombre(const std::string& nombre) { m_nombre = nombre; }
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
    // Temporizadores de disparo e invulnerabilidad
    m_tiempoDesdeDisparo += dt;
    if (m_tiempoInvulnerable > 0.f)
        m_tiempoInvulnerable -= dt;

    // Movimiento con WASD
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
    // Parpadeo mientras es invulnerable (se oculta cada 0.1 s)
    if (esInvulnerable() && static_cast<int>(m_tiempoInvulnerable * 10.f) % 2 == 0)
        return;

    target.draw(m_forma, states);
}

void Jugador::apuntarHacia(sf::Vector2f objetivo) {
    const sf::Vector2f d = objetivo - m_forma.getPosition();
    if (d == sf::Vector2f{0.f, 0.f}) return;
    m_direccion = d.normalized();
    m_forma.setRotation(d.angle());
}

sf::Vector2f Jugador::getDireccion() const { return m_direccion; }

void Jugador::disparar(std::vector<Proyectil>& proyectiles) {
    // Respeta la cadencia (ms entre disparos)
    if (m_tiempoDesdeDisparo * 1000.f < m_cadencia)
        return;
    m_tiempoDesdeDisparo = 0.f;

    // Abanico centrado en la direccion de la mira
    const float centro = (m_cantidadProyectiles - 1) / 2.f;
    for (int i = 0; i < m_cantidadProyectiles; i++) {
        const sf::Vector2f dir = m_direccion.rotatedBy(sf::degrees((i - centro) * AnguloAbanico));
        proyectiles.emplace_back(m_forma.getPosition() + dir * 25.f, dir,
                                 m_velocidadProyectil * TamCasillero,
                                 m_alcance * TamCasillero, m_danio, false);
    }
}

void Jugador::recibirDanio(int danio) {
    // Mientras es invulnerable no recibe danio
    if (esInvulnerable() || !estaVivo())
        return;

    setVida(m_vida - danio);
    m_tiempoInvulnerable = DuracionInvulnerable;
}

bool Jugador::estaVivo() const { return m_vida > 0; }
bool Jugador::esInvulnerable() const { return m_tiempoInvulnerable > 0.f; }

void Jugador::limitarA(const sf::FloatRect& area) {
    const sf::Vector2f mitad = m_forma.getSize() / 2.f;
    sf::Vector2f pos = m_forma.getPosition();
    pos.x = std::clamp(pos.x, area.position.x + mitad.x, area.position.x + area.size.x - mitad.x);
    pos.y = std::clamp(pos.y, area.position.y + mitad.y, area.position.y + area.size.y - mitad.y);
    m_forma.setPosition(pos);
}
