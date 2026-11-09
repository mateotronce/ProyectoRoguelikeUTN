#include "Sala.h"
#include "Constantes.h"
#include <algorithm>

// Lugares donde aparecen los enemigos, en orden (esquinas y centro)
const sf::Vector2f PuntosAparicion[] = {
    {130.f, 130.f}, {670.f, 130.f}, {130.f, 470.f}, {670.f, 470.f}, {400.f, 300.f}
};

// Si el proyectil toca a un enemigo de la lista, le hace danio y se apaga
template <class T>
void impactarEnemigos(Proyectil& proyectil, std::vector<T>& enemigos) {
    for (T& enemigo : enemigos) {
        if (proyectil.estaActivo() && chocan(proyectil.getCaja(), enemigo.getCaja())) {
            enemigo.recibirDanio(proyectil.getDanio());
            proyectil.desactivar();
        }
    }
}

// Saca de la lista a los enemigos sin vida
template <class T>
void borrarMuertos(std::vector<T>& enemigos) {
    enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(),
                                  [](const T& e) { return !e.estaVivo(); }),
                   enemigos.end());
}

template <class T>
void dibujarTodos(sf::RenderTarget& target, sf::RenderStates states, const std::vector<T>& lista) {
    for (const T& elemento : lista)
        target.draw(elemento, states);
}

Sala::Sala(const RegistroSala& datos) {
    m_idSala = datos.idSala;
    m_tipo = datos.tipo;
    m_puertas[0] = datos.salaNorte;
    m_puertas[1] = datos.salaSur;
    m_puertas[2] = datos.salaEste;
    m_puertas[3] = datos.salaOeste;
    m_opcional = datos.opcional;
}

int Sala::getId() const { return m_idSala; }
int Sala::getTipo() const { return m_tipo; }
int Sala::getPuerta(int direccion) const {
    if (direccion < 0 || direccion >= 4) return -1;
    return m_puertas[direccion];
}
bool Sala::esOpcional() const { return m_opcional; }
bool Sala::estaCompletada() const { return m_completada; }
void Sala::marcarCompletada() { m_completada = true; }
bool Sala::tieneEnemigos() const { return m_tipo == 2 || m_tipo == 5; }

void Sala::cargarEnemigos(const std::vector<RegistroEnemigo>& enemigos) {
    m_enemigosDeLaSala = enemigos;
}

void Sala::cargarRecompensas(const std::vector<Recompensa>& recompensas) {
    m_recompensas = recompensas;

    // Una sola va al centro; en los altares se reparten en fila
    const float separacion = 150.f;
    const float inicio = 400.f - separacion * (m_recompensas.size() - 1) / 2.f;
    for (size_t i = 0; i < m_recompensas.size(); i++)
        m_recompensas[i].setPosicion({inicio + separacion * i, 300.f});
}

void Sala::entrar() {
    // Las salas sin enemigos quedan completadas apenas se entra
    if (!tieneEnemigos()) {
        m_completada = true;
        return;
    }
    if (m_completada)
        return;

    // Combate: puertas trabadas y enemigos en 1 segundo
    m_acolitos.clear();
    m_hechiceros.clear();
    m_guardianes.clear();
    m_enCombate = true;
    m_tiempoParaAparecer = EsperaAparicion;
}

void Sala::hacerAparecerEnemigos() {
    for (size_t i = 0; i < m_enemigosDeLaSala.size(); i++) {
        const RegistroEnemigo& datos = m_enemigosDeLaSala[i];
        const sf::Vector2f pos = PuntosAparicion[i % 5];

        // tipo: 1 cuerpo a cuerpo, 2 a distancia, 3 tanque
        if (datos.tipo == 1) m_acolitos.emplace_back(datos, pos);
        else if (datos.tipo == 2) m_hechiceros.emplace_back(datos, pos);
        else if (datos.tipo == 3) m_guardianes.emplace_back(datos, pos);
    }
}

bool Sala::actualizar(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles) {
    // Espera antes de que aparezcan los enemigos
    if (m_enCombate && m_tiempoParaAparecer > 0.f) {
        m_tiempoParaAparecer -= dt;
        if (m_tiempoParaAparecer <= 0.f)
            hacerAparecerEnemigos();
    }

    actualizarEnemigos(dt, jugador, proyectiles);
    actualizarProyectiles(dt, jugador, proyectiles);

    // Sala limpia: se destraban las puertas y aparece la recompensa
    bool seCompleto = false;
    if (m_enCombate && m_tiempoParaAparecer <= 0.f && !quedanEnemigos()) {
        m_enCombate = false;
        m_completada = true;
        seCompleto = true;
    }

    revisarRecompensas(jugador);
    return seCompleto;
}

void Sala::actualizarEnemigos(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles) {
    // Movimiento y ataque por contacto
    for (Acolito& acolito : m_acolitos) {
        acolito.actualizar(dt, jugador);
        if (chocan(acolito.getCaja(), jugador.getCaja()))
            acolito.Ataque(jugador);
    }
    for (Guardian& guardian : m_guardianes) {
        guardian.actualizar(dt, jugador);
        if (chocan(guardian.getCaja(), jugador.getCaja()))
            guardian.Ataque(jugador);
    }
    for (Hechicero& hechicero : m_hechiceros)
        hechicero.actualizar(dt, jugador, proyectiles);
}

void Sala::actualizarProyectiles(float dt, Jugador& jugador, std::vector<Proyectil>& proyectiles) {
    for (Proyectil& proyectil : proyectiles) {
        proyectil.actualizar(dt);

        // Se apaga al llegar a la pared
        if (!AreaSala.contains(proyectil.getPosicion()))
            proyectil.desactivar();

        if (proyectil.esEnemigo()) {
            if (proyectil.estaActivo() && chocan(proyectil.getCaja(), jugador.getCaja())) {
                jugador.recibirDanio(proyectil.getDanio());
                proyectil.desactivar();
            }
        } else {
            impactarEnemigos(proyectil, m_acolitos);
            impactarEnemigos(proyectil, m_hechiceros);
            impactarEnemigos(proyectil, m_guardianes);
        }
    }

    // Limpieza de muertos y proyectiles apagados
    borrarMuertos(m_acolitos);
    borrarMuertos(m_hechiceros);
    borrarMuertos(m_guardianes);
    proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(),
                                     [](const Proyectil& p) { return !p.estaActivo(); }),
                      proyectiles.end());
}

void Sala::revisarRecompensas(Jugador& jugador) {
    if (!recompensasVisibles())
        return;

    // Se toma caminando encima; en los altares las demas desaparecen
    for (const Recompensa& recompensa : m_recompensas) {
        if (chocan(recompensa.getCaja(), jugador.getCaja())) {
            recompensa.aplicar(jugador);
            m_recompensaTomada = true;
            return;
        }
    }
}

bool Sala::quedanEnemigos() const {
    return !m_acolitos.empty() || !m_hechiceros.empty() || !m_guardianes.empty();
}

bool Sala::estaLimpia() const {
    return m_completada || !tieneEnemigos();
}

bool Sala::puertasAbiertas() const {
    return !m_enCombate;
}

bool Sala::recompensasVisibles() const {
    return m_completada && !m_enCombate && !m_recompensaTomada && !m_recompensas.empty();
}

const std::vector<Recompensa>& Sala::getRecompensas() const {
    return m_recompensas;
}

sf::FloatRect Sala::getZonaPuerta(int direccion) {
    switch (direccion) {
        case 0:  return sf::FloatRect({350.f, 50.f}, {100.f, 8.f});   // Norte
        case 1:  return sf::FloatRect({350.f, 542.f}, {100.f, 8.f});  // Sur
        case 2:  return sf::FloatRect({742.f, 250.f}, {8.f, 100.f});  // Este
        default: return sf::FloatRect({50.f, 250.f}, {8.f, 100.f});   // Oeste
    }
}

sf::Vector2f Sala::getEntrada(int direccion) {
    switch (direccion) {
        case 0:  return {400.f, 95.f};   // Norte
        case 1:  return {400.f, 505.f};  // Sur
        case 2:  return {705.f, 300.f};  // Este
        default: return {95.f, 300.f};   // Oeste
    }
}

void Sala::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Piso con un borde grueso que hace de pared
    sf::RectangleShape piso(AreaSala.size);
    piso.setPosition(AreaSala.position);
    piso.setFillColor(sf::Color(40, 35, 45));
    piso.setOutlineThickness(50.f);
    piso.setOutlineColor(sf::Color(90, 80, 70));
    target.draw(piso, states);

    // Puertas: oscuras si estan abiertas, rojas si estan trabadas
    const sf::FloatRect huecos[4] = {
        sf::FloatRect({350.f, 20.f}, {100.f, 30.f}),
        sf::FloatRect({350.f, 550.f}, {100.f, 30.f}),
        sf::FloatRect({750.f, 250.f}, {30.f, 100.f}),
        sf::FloatRect({20.f, 250.f}, {30.f, 100.f})
    };
    for (int i = 0; i < 4; i++) {
        if (m_puertas[i] == -1)
            continue;

        sf::RectangleShape puerta(huecos[i].size);
        puerta.setPosition(huecos[i].position);
        puerta.setFillColor(puertasAbiertas() ? sf::Color(15, 12, 15) : sf::Color(140, 40, 30));
        target.draw(puerta, states);
    }

    if (recompensasVisibles())
        dibujarTodos(target, states, m_recompensas);

    dibujarTodos(target, states, m_acolitos);
    dibujarTodos(target, states, m_hechiceros);
    dibujarTodos(target, states, m_guardianes);
}
