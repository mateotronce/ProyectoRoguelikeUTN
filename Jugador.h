#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Jugador: public sf::Drawable
{

private:
    std::string NombreJugador;
    int Vida = 100;
    int Danio = 10;
    float Velocidad = 5;

    int VidaMaxima;
    int CantidadProyectiles;
    int Alcance;
    int VelocidadProyectil;
    int Cadencia;

    sf::Sprite _sprite;
    sf::Texture _texture;



public:

///constructor///
    Jugador();

    /// Getters ///
    int getVida();
    int getDanio();
    float getVel();


    /// Setters ///
    void setVida(int _vida);
    void setDanio(int _danio);
    void setVel(float _vel);

    /// sfml

    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
