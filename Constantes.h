#pragma once
#include <SFML/Graphics.hpp>

// tamaño de un casillero en pixeles
// las velocidades y distancias del documento estan en casilleros, se multiplican por esto
constexpr float TamCasillero = 50.f;

// area jugable de una sala (lo de afuera son paredes)
inline const sf::FloatRect AreaSala({50.f, 50.f}, {700.f, 500.f});

// true si dos cajas se tocan
inline bool chocan(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}
