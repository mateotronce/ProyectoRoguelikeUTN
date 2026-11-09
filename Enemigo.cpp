#include "Enemigo.h"
#include "Constantes.h"

Enemigo::Enemigo(const RegistroEnemigo& datos, sf::Vector2f pos, sf::Vector2f tamanio, sf::Color color)
    : m_forma(tamanio)
{

    Vida = datos.vida;
    Danio = datos.danio;
    Velocidad = datos.velocidad;
    Puntos = datos.puntos;
    CadenciaDisparo = datos.cadenciaDisparo;

    // Forma centrada en su posicion
    m_forma.setOrigin(tamanio / 2.f);
    m_forma.setPosition(pos);
    m_forma.setFillColor(color);

}

// metodos

int Enemigo::getVida() const
{
    return Vida;
}
void Enemigo::setVida(int valor)
{
    Vida = valor;
}
int Enemigo::getDanio() const
{
    return Danio;
}
void Enemigo::setDanio(int valor)
{
    Danio = valor;
}
int Enemigo::getVel() const
{
    return Velocidad;
}
void Enemigo::setVel(int valor)
{
    Velocidad = valor;
}
int Enemigo::getPuntos() const
{
    return Puntos;
}
int Enemigo::getCadenciaDisparo() const
{
    return CadenciaDisparo;
}

void Enemigo::recibirDanio(int valor)
{
    Vida -= valor;
    if (Vida < 0)
        Vida = 0;
}
bool Enemigo::estaVivo() const
{
    return Vida > 0;
}

sf::Vector2f Enemigo::getPosicion() const
{
    return m_forma.getPosition();
}
sf::FloatRect Enemigo::getCaja() const
{
    return m_forma.getGlobalBounds();
}

void Enemigo::moverHacia(sf::Vector2f objetivo, float dt, float distanciaMinima)
{
    const sf::Vector2f d = objetivo - m_forma.getPosition();
    const float distancia = d.length();
    if (distancia <= distanciaMinima)
        return;

    // No pasarse de la distancia minima en este frame
    float movimiento = Velocidad * TamCasillero * dt;
    if (movimiento > distancia - distanciaMinima)
        movimiento = distancia - distanciaMinima;

    m_forma.move(d / distancia * movimiento);
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_forma, states);
}
