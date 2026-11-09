#pragma once
#include "Objeto.h"
#include <string>
#include <SFML/Graphics.hpp>

// Una recompensa tiene una mejora y, en los altares, una maldicion.
class Recompensa : public sf::Drawable {
private:
    int m_id;
    std::string m_nombre;
    Objeto m_mejora;
    int m_multiplicador;
    Objeto m_maldicion;
    bool m_tieneMaldicion;

    sf::CircleShape m_forma;
    sf::RectangleShape m_pedestal;

    void prepararForma();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Recompensa();
    Recompensa(int id, std::string nombre, Objeto mejora, int multiplicador = 1);
    Recompensa(int id, std::string nombre, Objeto mejora,
               int multiplicador, Objeto maldicion);

    int getId() const;
    std::string getNombre() const;
    // Nombre y efectos, para mostrar en pantalla
    std::string getDescripcion() const;
    bool tieneMaldicion() const;
    void aplicar(Jugador& jugador) const;

    void setPosicion(sf::Vector2f pos);
    sf::Vector2f getPosicion() const;
    sf::FloatRect getCaja() const;
};
