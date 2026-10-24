#include "Mira.h"

Mira::Mira()
    : m_circulo(10.f), m_horizontal({24.f, 2.f}), m_vertical({2.f, 24.f})
{
    // Origen en el centro de cada pieza, para que todas se centren en el mismo punto
    m_circulo.setOrigin({10.f, 10.f});
    m_circulo.setFillColor(sf::Color::Transparent);
    m_circulo.setOutlineThickness(2.f);
    m_circulo.setOutlineColor(sf::Color::Red);

    m_horizontal.setOrigin({12.f, 1.f});
    m_horizontal.setFillColor(sf::Color::Red);

    m_vertical.setOrigin({1.f, 12.f});
    m_vertical.setFillColor(sf::Color::Red);
}

void Mira::setPosicion(sf::Vector2f pos)
{
    m_circulo.setPosition(pos);
    m_horizontal.setPosition(pos);
    m_vertical.setPosition(pos);
}

void Mira::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_circulo, states);
    target.draw(m_horizontal, states);
    target.draw(m_vertical, states);
}
