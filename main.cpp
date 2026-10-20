#include <SFML/Graphics.hpp>
#include "Jugador.h"

int main()
{
    Jugador jugador;

    // inicializar window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Diez Sellos");
    window.setFramerateLimit(60);



    // game loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // CMD - comandos



        // update

        jugador.update();

        // dibujar

        window.clear();

        window.draw(jugador);

        window.display();


    }



}
