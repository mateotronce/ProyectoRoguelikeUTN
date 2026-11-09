#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "Constantes.h"
#include "Jugador.h"
#include "Mira.h"
#include "Mapa.h"
#include "Proyectil.h"
#include "CargadorDatos.h"
#include "Generadordatos.h"

// Corazones arriba a la izquierda (no se muestran con la maldicion de vida oculta)
void dibujarVida(sf::RenderWindow& window, const Jugador& jugador)
{
    if (jugador.tieneVidaOculta())
        return;

    sf::RectangleShape corazon({18.f, 18.f});
    for (int i = 0; i < jugador.getVidaMaxima(); i++)
    {
        corazon.setPosition({15.f + i * 24.f, 16.f});
        corazon.setFillColor(i < jugador.getVida() ? sf::Color::Red : sf::Color(70, 20, 20));
        window.draw(corazon);
    }
}

// Numero de sala, estadisticas del jugador y nombres de las recompensas
void dibujarTextos(sf::RenderWindow& window, const sf::Font& fuente, const Jugador& jugador, const Sala& sala)
{
    sf::Text texto(fuente, "Sala " + std::to_string(sala.getId()), 18);
    texto.setPosition({680.f, 14.f});
    window.draw(texto);

    texto.setCharacterSize(14);
    texto.setString("Danio " + std::to_string(jugador.getDanio())
                    + "  Vel " + std::to_string(static_cast<int>(jugador.getVel()))
                    + "  Proy " + std::to_string(jugador.getCantidadProyectiles())
                    + "  Alc " + std::to_string(jugador.getAlcance())
                    + "  Cad " + std::to_string(static_cast<int>(jugador.getCadencia())));
    texto.setPosition({60.f, 565.f});
    window.draw(texto);

    if (!sala.recompensasVisibles())
        return;

    // Nombre centrado debajo de cada recompensa
    for (const Recompensa& recompensa : sala.getRecompensas())
    {
        texto.setString(recompensa.getDescripcion());
        texto.setOrigin({texto.getLocalBounds().size.x / 2.f, 0.f});
        texto.setPosition(recompensa.getPosicion() + sf::Vector2f{0.f, 32.f});
        window.draw(texto);
    }
}


int main()
{

    generarDatosIniciales();

    // Datos fijos del juego y armado de las 10 salas
    CargadorDatos datos;
    Mapa mapa;
    if (!datos.cargar() || !datos.armarMapa(mapa))
    {
        std::cerr << "No se pudieron cargar los archivos de data/\n";
        return 1;
    }

    sf::Font fuente;
    if (!fuente.openFromFile("fonts/tuffy.ttf"))
    {
        std::cerr << "No se pudo cargar fonts/tuffy.ttf\n";
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Diez Sellos");
    window.setFramerateLimit(60);

    Jugador jugador({400.f, 300.f});
    Mira mira;
    std::vector<Proyectil> proyectiles;

    // Provisorio hasta la etapa 3 (pantallas de victoria y derrota): vuelve a la sala 1
    auto reiniciarPartida = [&]()
    {
        jugador = Jugador({400.f, 300.f});
        proyectiles.clear();
        datos.armarMapa(mapa);
        mapa.getSalaActual().entrar();
    };
    reiniciarPartida();

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
        // se limita dt para que un tiron (ej: mover la ventana) no teletransporte todo
        const float dt = std::min(reloj.restart().asSeconds(), 0.05f);
        const sf::Vector2f posMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));


        // jugador
        jugador.actualizar(dt);
        jugador.limitarA(AreaSala);
        jugador.apuntarHacia(posMouse);
        mira.setPosicion(posMouse);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            jugador.disparar(proyectiles);

        // sala actual: enemigos, proyectiles y recompensas
        const bool salaCompletada = mapa.getSalaActual().actualizar(dt, jugador, proyectiles);

        // cambio de sala al pisar una puerta abierta
        for (int direccion = 0; direccion < 4; direccion++)
        {
            if (chocan(jugador.getCaja(), Sala::getZonaPuerta(direccion)) && mapa.cambiarSala(direccion))
            {
                // se entra por la puerta opuesta de la sala nueva
                const int opuesta[4] = {1, 0, 3, 2};
                jugador.setPosicion(Sala::getEntrada(opuesta[direccion]));
                proyectiles.clear();
                mapa.getSalaActual().entrar();
                break;
            }
        }

        // provisorio: al morir o ganar se reinicia la partida
        if (!jugador.estaVivo() || (salaCompletada && mapa.getNumeroSalaActual() == 10))
            reiniciarPartida();

        // dibujar

        window.clear(sf::Color(20, 18, 22));
        window.draw(mapa.getSalaActual());
        for (const Proyectil& proyectil : proyectiles)
            window.draw(proyectil);
        window.draw(jugador);
        dibujarVida(window, jugador);
        dibujarTextos(window, fuente, jugador, mapa.getSalaActual());
        window.draw(mira);
        window.display();
    }
}
