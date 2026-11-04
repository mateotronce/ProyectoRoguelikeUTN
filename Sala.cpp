#include "Sala.h"

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

void Sala::cargarEnemigos(const std::vector<Acolito>& acolitos,
                         const std::vector<Hechicero>& hechiceros,
                         const std::vector<Guardian>& guardianes) {
    m_acolitos = acolitos;
    m_hechiceros = hechiceros;
    m_guardianes = guardianes;
    m_enemigosCargados = true;
}

void Sala::cargarRecompensas(const std::vector<Recompensa>& recompensas) {
    m_recompensas = recompensas;
}

bool Sala::estaLimpia() {
    if ((m_tipo == 2 || m_tipo == 5) && !m_enemigosCargados)
        return false;

    for (Acolito& enemigo : m_acolitos)
        if (enemigo.getVida() > 0) return false;
    for (Hechicero& enemigo : m_hechiceros)
        if (enemigo.getVida() > 0) return false;
    for (Guardian& enemigo : m_guardianes)
        if (enemigo.getVida() > 0) return false;
    return true;
}

bool Sala::puertasAbiertas() {
    if (m_tipo == 1 || m_tipo == 3 || m_tipo == 4)
        return true;
    return m_completada || estaLimpia();
}

std::vector<Recompensa>& Sala::getRecompensas() {
    return m_recompensas;
}
