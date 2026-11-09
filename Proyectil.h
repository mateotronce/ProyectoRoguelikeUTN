#pragma once
#include <SFML/Graphics.hpp>

// proyectil del jugador o de un enemigo
// avanza en linea recta hasta recorrer su alcance o chocar con algo
class Proyectil : public sf::Drawable {
public:
    // velocidad y alcance en pixeles
    Proyectil(sf::Vector2f pos, sf::Vector2f direccion, float velocidad,
              float alcance, int danio, bool esEnemigo);

    void actualizar(float dt);
    void desactivar();

    bool estaActivo() const;
    bool esEnemigo() const;
    int getDanio() const;
    sf::Vector2f getPosicion() const;
    sf::FloatRect getCaja() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape m_forma;
    sf::Vector2f m_velocidad;   // pixeles por segundo
    float m_alcance;            // pixeles que puede recorrer
    float m_recorrido = 0.f;
    int m_danio;
    bool m_esEnemigo;
    bool m_activo = true;
};
