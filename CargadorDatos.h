#pragma once
#include <string>
#include <vector>
#include "Registros.h"
#include "Objeto.h"
#include "Recompensa.h"

class Mapa;

// Lee los 5 archivos fijos al iniciar y arma las salas con sus enemigos y recompensas
class CargadorDatos {
private:
    std::vector<RegistroSala> m_salas;
    std::vector<RegistroSalaEnemigo> m_salaEnemigos;
    std::vector<RegistroEnemigo> m_enemigos;
    std::vector<RegistroModificador> m_modificadores;
    std::vector<RegistroRecompensa> m_recompensas;

public:
    // false si falta algun archivo o esta vacio
    bool cargar();

    // Crea las 10 salas en el mapa y les carga enemigos y recompensas
    bool armarMapa(Mapa& mapa) const;

    RegistroEnemigo getEnemigo(int idEnemigo) const;
    Objeto getModificador(int idModificador) const;

    // Un registro por cada enemigo que aparece (si hay 3 acolitos, 3 registros)
    std::vector<RegistroEnemigo> getEnemigosDeSala(int idSala) const;
    std::vector<Recompensa> getRecompensasDeSala(int idSala) const;
};
