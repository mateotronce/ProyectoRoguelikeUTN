#include "Mapa.h"

bool Mapa::buscarPosicion(int idSala, int& fila, int& columna) const {
    for (int f = 0; f < 4; f++) {
        for (int c = 0; c < 6; c++) {
            if (m_matriz[f][c] == idSala) {
                fila = f;
                columna = c;
                return true;
            }
        }
    }
    return false;
}

int Mapa::getIdEnPosicion(int fila, int columna) const {
    if (fila < 0 || fila >= 4 || columna < 0 || columna >= 6)
        return 0;

    return m_matriz[fila][columna];
}

bool Mapa::cargar(const std::vector<RegistroSala>& registros) {
    if (registros.size() != 10)
        return false;

    Sala nuevasSalas[10];
    bool vistos[10] = {false};

    for (int i = 0; i < 10; i++) {
        const RegistroSala& datos = registros[i];

        if (datos.idSala < 1 || datos.idSala > 10)
            return false;
        if (vistos[datos.idSala - 1])
            return false;
        if (datos.tipo < 1 || datos.tipo > 5)
            return false;

        int puertas[4] = {
            datos.salaNorte, datos.salaSur,
            datos.salaEste, datos.salaOeste
        };

        for (int p = 0; p < 4; p++) {
            if (puertas[p] != -1 && (puertas[p] < 1 || puertas[p] > 10))
                return false;
        }

        vistos[datos.idSala - 1] = true;
        nuevasSalas[datos.idSala - 1] = Sala(datos);
    }

    for (int i = 0; i < 10; i++) {
        if (!vistos[i])
            return false;
    }

    for (int i = 0; i < 10; i++)
        m_salas[i] = nuevasSalas[i];

    m_salaActual = 1;
    m_cargado = true;
    return true;
}

bool Mapa::estaCargado() const {
    return m_cargado;
}

Sala& Mapa::getSalaActual() {
    return m_salas[m_salaActual - 1];
}

Sala* Mapa::getSala(int idSala) {
    if (!m_cargado || idSala < 1 || idSala > 10)
        return nullptr;

    return &m_salas[idSala - 1];
}

int Mapa::getNumeroSalaActual() const {
    return m_salaActual;
}

bool Mapa::cambiarSala(int direccion) {
    if (!m_cargado || direccion < 0 || direccion > 3)
        return false;

    Sala& actual = getSalaActual();
    if (!actual.puertasAbiertas())
        return false;

    int fila = 0;
    int columna = 0;
    if (!buscarPosicion(m_salaActual, fila, columna))
        return false;

    // Buscamos la casilla vecina segun la direccion elegida.
    if (direccion == 0) fila--;          // Norte
    else if (direccion == 1) fila++;     // Sur
    else if (direccion == 2) columna++;  // Este
    else columna--;                      // Oeste

    int destino = getIdEnPosicion(fila, columna);
    if (destino == 0)
        return false;

    // La puerta tambien debe existir en los datos de esa sala.
    // Al crear Salas.dat, las conexiones deben coincidir con esta matriz.
    if (actual.getPuerta(direccion) != destino)
        return false;

    m_salaActual = destino;
    return true;
}

void Mapa::marcarCompletada(int idSala) {
    Sala* sala = getSala(idSala);
    if (sala != nullptr)
        sala->marcarCompletada();
}
