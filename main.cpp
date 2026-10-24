#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Mira.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Diez Sellos");
    window.setFramerateLimit(60);

    Jugador jugador({400.f, 300.f});

    Mira mira;

    sf::Clock reloj;

    window.setMouseCursorVisible(false);

    // game loop
    while (window.isOpen())
    {
        // eventos
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        // update
        const float dt = reloj.restart().asSeconds();
        const sf::Vector2f posMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));


        jugador.actualizar(dt);
        jugador.apuntarHacia(posMouse);
        mira.setPosicion(posMouse);

        // dibujar

        window.clear();
        window.draw(jugador);
        window.draw(mira);
        window.display();
    }
}
