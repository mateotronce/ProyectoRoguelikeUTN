#pragma once
#include "Registros.h"
#include "Acolito.h"
#include "Hechicero.h"
#include "Guardian.h"
#include "Recompensa.h"
#include <vector>

class Sala {
private:
    int m_idSala = 0;
    int m_tipo = 0;
    int m_puertas[4] = {-1, -1, -1, -1};
    bool m_completada = false;
    bool m_opcional = false;
    bool m_enemigosCargados = false;

    std::vector<Acolito> m_acolitos;
    std::vector<Hechicero> m_hechiceros;
    std::vector<Guardian> m_guardianes;
    std::vector<Recompensa> m_recompensas;

public:
    Sala() = default;
    Sala(const RegistroSala& datos);

    int getId() const;
    int getTipo() const;
    int getPuerta(int direccion) const;
    bool esOpcional() const;
    bool estaCompletada() const;
    void marcarCompletada();

    void cargarEnemigos(const std::vector<Acolito>& acolitos,
                       const std::vector<Hechicero>& hechiceros,
                       const std::vector<Guardian>& guardianes);
    void cargarRecompensas(const std::vector<Recompensa>& recompensas);

    bool estaLimpia();
    bool puertasAbiertas();

    std::vector<Recompensa>& getRecompensas();
};
