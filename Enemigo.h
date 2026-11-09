#pragma once
#include <SFML/Graphics.hpp>
#include "Registros.h"

// Base de los tres enemigos. Las estadisticas salen de Enemigos.dat
class Enemigo : public sf::Drawable {

private:
    int Vida;
    int Danio;
    int Velocidad;        // casilleros por segundo
    int Puntos;
    int CadenciaDisparo;  // ms entre disparos (0 = no dispara)

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::RectangleShape m_forma;

    // Avanza hacia el objetivo hasta quedar a "distanciaMinima" pixeles
    void moverHacia(sf::Vector2f objetivo, float dt, float distanciaMinima = 0.f);

public:

    Enemigo(const RegistroEnemigo& datos, sf::Vector2f pos, sf::Vector2f tamanio, sf::Color color);

    int getVida() const;
    int getDanio() const;
    int getVel() const;
    int getPuntos() const;
    int getCadenciaDisparo() const;

    void setVida(int _vida);
    void setDanio(int _danio);
    void setVel(int _vel);

    void recibirDanio(int _danio);
    bool estaVivo() const;

    sf::Vector2f getPosicion() const;
    sf::FloatRect getCaja() const;
};
