#pragma once
#include "Registros.h"
#include "Acolito.h"
#include "Hechicero.h"
#include "Guardian.h"
#include "Recompensa.h"
#include "Proyectil.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Sala : public sf::Drawable {
private:
    static constexpr float EsperaAparicion = 1.f;  // segundos

    int m_idSala = 0;
    int m_tipo = 0;
    int m_puertas[4] = {-1, -1, -1, -1};
    bool m_completada = false;
    bool m_opcional = false;

    bool m_enCombate = false;          // puertas trabadas
    float m_tiempoParaAparecer = 0.f;
    bool m_recompensaTomada = false;

    // Quienes aparecen al entrar (salen de SalaEnemigos.dat)
    std::vector<RegistroEnemigo> m_enemigosDeLaSala;

    std::vector<Acolito> m_acolitos;
    std::vector<Hechicero> m_hechiceros;
    std::vector<Guardian> m_guardianes;
    std::vector<Recompensa> m_recompensas;

    void hacerAparecerEnemigos();
    void actualizarEnemigos(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles);
    void actualizarProyectiles(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles);
    void revisarRecompensas(Jugador& jugador);
    bool quedanEnemigos() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Sala() = default;
    Sala(const RegistroSala& datos);

    int getId() const;
    int getTipo() const;
    int getPuerta(int direccion) const;
    bool esOpcional() const;
    bool estaCompletada() const;
    void marcarCompletada();
    bool tieneEnemigos() const;   // sala de combate o final

    void cargarEnemigos(const std::vector<RegistroEnemigo>& enemigos);
    void cargarRecompensas(const std::vector<Recompensa>& recompensas);

    // Se llama al entrar: si la sala no esta completada traba las puertas
    void entrar();

    // Devuelve true en el frame en que se termina de limpiar la sala
    bool actualizar(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles);

    bool estaLimpia() const;
    bool puertasAbiertas() const;
    bool recompensasVisibles() const;

    const std::vector<Recompensa>& getRecompensas() const;

    // 0 = norte, 1 = sur, 2 = este, 3 = oeste
    // Zona que hay que pisar para cruzar la puerta
    static sf::FloatRect getZonaPuerta(int direccion);
    // Donde aparece el jugador al llegar por esa puerta
    static sf::Vector2f getEntrada(int direccion);
};
