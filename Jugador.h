#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Jugador: public sf::Drawable
{

private:
    std::string NombreJugador;

    const int VidaMaxima = 100;
    int Vida = VidaMaxima;
    int Danio = 10;
    float Velocidad = 5;

    int CantidadProyectiles = 0;
    int Alcance = 0;
    int VelocidadProyectil = 0;
    int Cadencia = 0;

    sf::Texture _texture;
    sf::Sprite _sprite;


public:

        ///constructor///
    Jugador();

        /// Getters ///

    int getVida();
    int getDanio();
    float getVel();
    int getCantidadProyectiles();
    int getAlcance();
    float getVelocidadProyectil();
    int getCadencia();

        /// Setters ///

    void setVida(int _vida);
    void setDanio(int _Danio);
    void setVel(float _vel) ;
    void setCantidadProyectiles(int _cantidadProyectiles);
    void setAlcance(int _alcance);
    void setVelocidadProyectil(float _velocidadProyectil);
    void setCadencia(int _cadencia);

    /// sfml

    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
