#include "Enemigo.h"
#include <cstring>

Enemigo::Enemigo(int _vida, int _danio, int _velocidad)
{

    Vida = _vida;
    Danio = _danio;
    Velocidad = _velocidad;

}

// metodos

int Enemigo::getVida()
{
    return Vida;
}
void Enemigo::setVida(int valor)
{
    Vida = valor;
}
int Enemigo::getDanio()
{
    return Danio;
}
void Enemigo::setDanio(int valor)
{
    Danio = valor;
}
int Enemigo::getVel()
{
    return Velocidad;
}
void Enemigo::setVel(int valor)
{
    Velocidad = valor;
}

