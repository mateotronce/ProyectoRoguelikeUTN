#include "Objeto.h"
#include "Jugador.h"

Objeto::Objeto() {
    m_id = -1;
    m_nombre = "";
    m_esMaldicion = false;
    m_atributo1 = 0;
    m_valor1 = 0;
    m_atributo2 = 0;
    m_valor2 = 0;
}

Objeto::Objeto(int id, std::string nombre, bool esMaldicion,
               int atributo1, int valor1, int atributo2, int valor2) {
    m_id = id;
    m_nombre = nombre;
    m_esMaldicion = esMaldicion;
    m_atributo1 = atributo1;
    m_valor1 = valor1;
    m_atributo2 = atributo2;
    m_valor2 = valor2;
}

int Objeto::getId() const { return m_id; }
std::string Objeto::getNombre() const { return m_nombre; }
bool Objeto::esMaldicion() const { return m_esMaldicion; }

void Objeto::aplicarEfecto(Jugador& jugador, int atributo, int valor) const {
    // Los numeros corresponden a los atributos de Modificadores.dat.
    switch (atributo) {
        case 1: jugador.setVidaMaxima(jugador.getVidaMaxima() + valor); break;
        case 2: jugador.setDanio(jugador.getDanio() + valor); break;
        case 3: jugador.setVel(jugador.getVel() + valor); break;
        case 4: jugador.setCantidadProyectiles(jugador.getCantidadProyectiles() + valor); break;
        case 5: jugador.setAlcance(jugador.getAlcance() + valor); break;
        case 6: jugador.setCadencia(jugador.getCadencia() + valor); break;
        case 7: jugador.setVidaOculta(valor == 1); break;
        case 8: jugador.setVida(jugador.getVida() + valor); break;
        case 9: jugador.setVelocidadProyectil(jugador.getVelocidadProyectil() + valor); break;
    }
}

void Objeto::aplicar(Jugador& jugador, int veces) const {
    for (int i = 0; i < veces; i++) {
        aplicarEfecto(jugador, m_atributo1, m_valor1);
        if (m_atributo2 != 0) {
            aplicarEfecto(jugador, m_atributo2, m_valor2);
        }
    }
}
