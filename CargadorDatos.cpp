#include "CargadorDatos.h"
#include "Archivo.h"
#include "Mapa.h"

// Lee todos los registros de un archivo
template <class T>
std::vector<T> leerTodo(const std::string& ruta)
{
    Archivo<T> arch(ruta);
    std::vector<T> registros;

    int cantidad = arch.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++)
        registros.push_back(arch.leer(i));

    return registros;
}

bool CargadorDatos::cargar()
{
    m_salas = leerTodo<RegistroSala>("data/Salas.dat");
    m_salaEnemigos = leerTodo<RegistroSalaEnemigo>("data/SalaEnemigos.dat");
    m_enemigos = leerTodo<RegistroEnemigo>("data/Enemigos.dat");
    m_modificadores = leerTodo<RegistroModificador>("data/Modificadores.dat");
    m_recompensas = leerTodo<RegistroRecompensa>("data/Recompensas.dat");

    return !m_salas.empty() && !m_salaEnemigos.empty() && !m_enemigos.empty()
        && !m_modificadores.empty() && !m_recompensas.empty();
}

bool CargadorDatos::armarMapa(Mapa& mapa) const
{
    if (!mapa.cargar(m_salas))
        return false;

    for (int id = 1; id <= 10; id++)
    {
        Sala* sala = mapa.getSala(id);
        sala->cargarEnemigos(getEnemigosDeSala(id));
        sala->cargarRecompensas(getRecompensasDeSala(id));
    }
    return true;
}

RegistroEnemigo CargadorDatos::getEnemigo(int idEnemigo) const
{
    for (const RegistroEnemigo& reg : m_enemigos)
        if (reg.idEnemigo == idEnemigo)
            return reg;

    return RegistroEnemigo();
}

Objeto CargadorDatos::getModificador(int idModificador) const
{
    for (const RegistroModificador& reg : m_modificadores)
        if (reg.idModificador == idModificador)
            return Objeto(reg.idModificador, reg.nombre, reg.esMaldicion,
                          reg.atributo1, reg.valor1, reg.atributo2, reg.valor2);

    return Objeto();
}

std::vector<RegistroEnemigo> CargadorDatos::getEnemigosDeSala(int idSala) const
{
    std::vector<RegistroEnemigo> enemigos;

    // Se repite el registro del enemigo segun la cantidad
    for (const RegistroSalaEnemigo& reg : m_salaEnemigos)
        if (reg.idSala == idSala)
            for (int i = 0; i < reg.cantidad; i++)
                enemigos.push_back(getEnemigo(reg.idEnemigo));

    return enemigos;
}

std::vector<Recompensa> CargadorDatos::getRecompensasDeSala(int idSala) const
{
    std::vector<Recompensa> recompensas;

    for (const RegistroRecompensa& reg : m_recompensas)
    {
        if (reg.idSala != idSala)
            continue;

        Objeto mejora = getModificador(reg.idMejora);

        // Las reliquias de los altares traen una maldicion
        if (reg.idMaldicion != -1)
            recompensas.push_back(Recompensa(reg.idRecompensa, reg.nombre, mejora,
                                             reg.multiplicador, getModificador(reg.idMaldicion)));
        else
            recompensas.push_back(Recompensa(reg.idRecompensa, reg.nombre, mejora, reg.multiplicador));
    }
    return recompensas;
}
