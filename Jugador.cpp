#include "Jugador.h"
#include <cstring>
#include <SFML/Graphics.hpp>

Jugador::Jugador()
    : _sprite(_texture){
    _sprite.setTexture(_texture, true);
}


// metodos

    int Jugador::getVida(){
        return Vida;
    }

    void Jugador::setVida(int _vida){

        if (_vida < 0){
            Vida = 0;
        }
        else if (_vida > VidaMaxima){
            Vida = VidaMaxima;
        }
        else{
            Vida = _vida;
        }
}

    int Jugador::getDanio(){
        return Danio;
    }

    void Jugador::setDanio(int valor){
        Danio = valor;
    }

    float Jugador::getVel(){
        return Velocidad;
    }

    void Jugador::setVel(float valor){
        Velocidad = valor;
    }

    int Jugador::getCantidadProyectiles(){
        return CantidadProyectiles;
    }

    void Jugador::setCantidadProyectiles(int valor){
        CantidadProyectiles = valor;
    }

    int Jugador::getAlcance(){
        return Alcance;
    }

    void Jugador::setAlcance(int valor){
        Alcance = valor;
    }

    float Jugador::getVelocidadProyectil(){
        return VelocidadProyectil;
    }

    void Jugador::setVelocidadProyectil(float valor){
        VelocidadProyectil = valor;
    }

    int Jugador::getCadencia(){
        return Cadencia;
    }

    void Jugador::setCadencia(int valor){
        Cadencia = valor;
    }



        ///MOVEMENT///
void Jugador::update(){

    // Movimiento WASD

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        _sprite.move({ 0.f, -Velocidad });
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        _sprite.move({ 0.f, Velocidad });
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        _sprite.move({ -Velocidad, 0.f });
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        _sprite.move({ Velocidad, 0.f });
    }


    // Limites de pantalla

    if(_sprite.getPosition().x < 0){
        _sprite.setPosition({0.f, _sprite.getPosition().y});
    }

    if(_sprite.getPosition().y < 0){
        _sprite.setPosition({_sprite.getPosition().x, 0.f});
    }

    if(_sprite.getPosition().x + _sprite.getGlobalBounds().size.x > 800){
        _sprite.setPosition({800.f - _sprite.getGlobalBounds().size.x, _sprite.getPosition().y});
    }

    if(_sprite.getPosition().y + _sprite.getGlobalBounds().size.y > 600){
        _sprite.setPosition({_sprite.getPosition().x, 600.f - _sprite.getGlobalBounds().size.y});
    }
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_sprite, states);
}

