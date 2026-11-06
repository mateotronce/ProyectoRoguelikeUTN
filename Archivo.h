#pragma once
#include <cstdio>
#include <string>

// template para cualquier registro de Registros.h.
// Archivo<RegistroEnemigo> arch("data/Enemigos.dat");

//   arch.guardar(reg);
//   RegistroEnemigo e = arch.leer(0);
//   int pos = arch.buscar(&RegistroEnemigo::idEnemigo, 3);



template <class T>
class Archivo
{
private:
    std::string _ruta;

public:
    Archivo(std::string ruta)
    {
        _ruta = ruta;
    }

    int getCantidadRegistros()
    {
        FILE *p = fopen(_ruta.c_str(), "rb");

        if (p == NULL)
        {
            return 0;
        }

        fseek(p, 0, SEEK_END);
        int bytes = ftell(p);
        fclose(p);

        return bytes / sizeof(T);
    }

    bool guardar(T reg)                              // agrega al final
    {
        FILE *p = fopen(_ruta.c_str(), "ab");

        if (p == NULL)
        {
            return false;
        }

        bool pudoEscribir = fwrite(&reg, sizeof(T), 1, p);
        fclose(p);
        return pudoEscribir;
    }

    bool guardar(T reg, int posicionAReemplazar)     // sobrescribe una posicion
    {
        FILE *p = fopen(_ruta.c_str(), "rb+");

        if (p == NULL)
        {
            return false;
        }

        fseek(p, posicionAReemplazar * sizeof(T), SEEK_SET);
        bool pudoEscribir = fwrite(&reg, sizeof(T), 1, p);
        fclose(p);
        return pudoEscribir;
    }

    T leer(int nroRegistro)
    {
        T aux;
        FILE *p = fopen(_ruta.c_str(), "rb");

        if (p == NULL)
        {
            return aux;
        }

        fseek(p, nroRegistro * sizeof(T), SEEK_SET);
        fread(&aux, sizeof(T), 1, p);
        fclose(p);
        return aux;
    }

    // devuelve la posicion del primer registro cuyo campo vale "valor", o -1.
    // "campo" es un puntero al campo del registro
    int buscar(int T::*campo, int valor)
    {
        int cantidad = getCantidadRegistros();

        for (int i = 0; i < cantidad; i++)
        {
            T aux = leer(i);
            if (aux.*campo == valor)
            {
                return i;
            }
        }
        return -1;
    }

    void vaciar()
    {
        FILE *p = fopen(_ruta.c_str(), "wb");

        if (p == NULL)
        {
            return;
        }

        fclose(p);
    }
};
