#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Jugador : public sf::Drawable
{
public:
    explicit Jugador(sf::Vector2f posInicial);

    /// Getters ///
    int   getVida() const;
    int   getDanio() const;
    float getVel() const;
    int   getCantidadProyectiles() const;
    int   getAlcance() const;
    float getVelocidadProyectil() const;
    float getCadencia() const;

    sf::Vector2f  getPosicion() const;
    sf::FloatRect getCaja() const;

    /// Setters ///
    void setVida(int vida);
    void setDanio(int danio);
    void setVel(float vel);
    void setCantidadProyectiles(int cantidad);
    void setAlcance(int alcance);
    void setVelocidadProyectil(float velocidad);
    void setCadencia(float cadencia);
    void setPosicion(sf::Vector2f pos);

    /// Lógica ///
    void actualizar(float dt);

    void apuntarHacia(sf::Vector2f objetivo);
    sf::Vector2f getDireccion() const;

private:
    // Lo exige sf::Drawable: permite hacer window.draw(jugador)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static constexpr int VidaMaxima = 100;

    std::string m_nombre;
    int   m_vida = VidaMaxima;
    int   m_danio = 10;
    float m_velocidad = 300.f;   // píxeles por segundo
    int   m_cantidadProyectiles = 0;
    int   m_alcance = 0;
    float m_velocidadProyectil = 0.f;
    float m_cadencia = 0.f;      // disparos por segundo

    sf::RectangleShape m_forma;

    sf::Vector2f m_direccion{1.f, 0.f};   // empieza mirando a la derecha
};
