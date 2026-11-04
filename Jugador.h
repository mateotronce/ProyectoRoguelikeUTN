#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Jugador : public sf::Drawable {
public:
    Jugador(sf::Vector2f posInicial);

    // Getters
    int getVida() const;
    int getVidaMaxima() const;
    bool tieneVidaOculta() const;
    int getDanio() const;
    float getVel() const;
    int getCantidadProyectiles() const;
    int getAlcance() const;
    float getVelocidadProyectil() const;
    float getCadencia() const;

    sf::Vector2f getPosicion() const;
    sf::FloatRect getCaja() const;

    // Setters
    void setVida(int vida);
    void setVidaMaxima(int vidaMaxima);
    void setVidaOculta(bool oculta);
    void setDanio(int danio);
    void setVel(float vel);
    void setCantidadProyectiles(int cantidad);
    void setAlcance(int alcance);
    void setVelocidadProyectil(float velocidad);
    void setCadencia(float cadencia);
    void setPosicion(sf::Vector2f pos);

    void actualizar(float dt);
    void apuntarHacia(sf::Vector2f objetivo);
    sf::Vector2f getDireccion() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static constexpr float TamCasillero = 50.f;

    std::string m_nombre;
    int m_vidaMaxima = 6;
    int m_vida = 6;
    int m_danio = 1;
    float m_velocidad = 3.f;
    int m_cantidadProyectiles = 1;
    int m_alcance = 6;
    float m_velocidadProyectil = 8.f;
    float m_cadencia = 400.f; // Milisegundos entre disparos
    bool m_vidaOculta = false;

    sf::RectangleShape m_forma;
    sf::Vector2f m_direccion{1.f, 0.f};
};
