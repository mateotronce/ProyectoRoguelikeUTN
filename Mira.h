#pragma once
#include <SFML/Graphics.hpp>

class Mira : public sf::Drawable
{
public:
    Mira();
    void setPosicion(sf::Vector2f pos);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape    m_circulo;
    sf::RectangleShape m_horizontal;
    sf::RectangleShape m_vertical;
};
