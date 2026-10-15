#include "Salas.h"


Salas::Salas()
{
    setIdSala(0);
    setTipo(0); // tal vez usar enum class Tipo ¿?
    setIdEnemigo(0);
    setIdRecompensa(0);
    _completada = false;

}



// metodos

void Salas::setIdSala(int id)
{

    _idSala = id;

}

int Salas::getIdSala()
{

    return _idSala;

}

void Salas::setTipo(int tipo)
{

    _tipo = tipo;

}

int Salas::getTipo()
{

    return _tipo;

}

void Salas::setIdEnemigo(int id)
{

    _idSala = id;

}

int Salas::getIdEnemigo()
{

    return _idEnemigo;

}

void Salas::setIdRecompensa(int id)
{

    _idRecompensa = id;

}

int Salas::getIdRecompensa()
{

    return _idRecompensa;

}



