#include "Jugador.h"
#include <cstring>
#include <SFML/Graphics.hpp>

Jugador::Jugador()
    : _sprite(_texture)
{

    _texture.loadFromFile("jugador.jpg");

    _sprite = sf::Sprite(_texture);



}

// metodos

int Jugador::getVida()
{
    return Vida;
}
void Jugador::setVida(int valor)
{
    Vida = valor;
}
int Jugador::getDanio()
{
    return Danio;
}
void Jugador::setDanio(int valor)
{
    Danio = valor;
}
float Jugador::getVel()
{
    return Velocidad;
}
void Jugador::setVel(float valor)
{
    Velocidad = valor;
}

void Jugador::update()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {

        _sprite.move({ 0.f, -Velocidad });

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {

        _sprite.move({ 0.f, Velocidad });

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {

        _sprite.move({ -Velocidad, 0.f });

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {

        _sprite.move({ Velocidad, 0.f });

    }

    if(_sprite.getPosition().x < 0)
    {

        _sprite.setPosition({0, _sprite.getPosition().y});

    }

    if(_sprite.getPosition().y < 0)
    {

        _sprite.setPosition({_sprite.getPosition().x, 0});

    }

    if(_sprite.getPosition().x + _sprite.getGlobalBounds().size.x > 800)
    {

        _sprite.setPosition({800 - _sprite.getGlobalBounds().size.x, _sprite.getPosition().y});

    }

    if(_sprite.getPosition().y + _sprite.getGlobalBounds().size.y > 600)
    {

        _sprite.setPosition({ _sprite.getPosition().x, 600 - _sprite.getGlobalBounds().size.y });

    }

}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(_sprite, states);

}

