#pragma once
#include <cstring>

// registros binarios de los archivos .dat
// son structs para poder grabarlos con fwrite/fread
// las entidades del juego (Sala, Enemigo, Objeto, Recompensa, Jugador) se construyen a partir de estos registros

// copia un texto a un char[] sin desbordarlo y siempre lo termina en '\0'.
inline void copiarTexto(char* destino, int tamanio, const char* origen) {
    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

// Representacion de una fila de Salas.dat.
struct RegistroSala {
    int idSala = 0;
    int tipo = 0;
    int salaNorte = -1;
    int salaSur = -1;
    int salaEste = -1;
    int salaOeste = -1;
    bool opcional = false;
};

// Una fila de SalaEnemigos.dat, cuantos enemigos de un tipo hay en una sala.
struct RegistroSalaEnemigo {
    int idSala = 0;
    int idEnemigo = 0;
    int cantidad = 0;
};

// Una fila de Enemigos.dat
struct RegistroEnemigo {
    int idEnemigo = 0;
    char nombre[30] = "";
    int tipo = 0;             // 1 cuerpo a cuerpo, 2 a distancia, 3 tanque
    int vida = 0;
    int danio = 0;
    int velocidad = 0;
    int cadenciaDisparo = 0;  // ms entre disparos (0 = no dispara)
    int puntos = 0;

    void setNombre(const char* texto) { copiarTexto(nombre, sizeof(nombre), texto); }
};

// Una fila de Modificadores.dat
// Atributos: 1 vida maxima, 2 danio, 3 velocidad, 4 proyectiles, 5 alcance,
//            6 cadencia, 7 vida oculta, 8 vida actual, 9 velocidad proyectil.
// "valor" es el cambio que se SUMA al atributo (negativo = resta).
struct RegistroModificador {
    int idModificador = 0;
    char nombre[30] = "";
    bool esMaldicion = false;
    int atributo1 = 0;
    int valor1 = 0;
    int atributo2 = 0;        // 0 = no hay segundo efecto
    int valor2 = 0;

    void setNombre(const char* texto) { copiarTexto(nombre, sizeof(nombre), texto); }
};

// Una fila de Recompensas.dat
struct RegistroRecompensa {
    int idRecompensa = 0;
    int idSala = 0;
    char nombre[30] = "";
    int idMejora = 0;         // id en Modificadores.dat
    int multiplicador = 1;    // veces que se aplica la mejora
    int idMaldicion = -1;     // -1 = sin maldicion

    void setNombre(const char* texto) { copiarTexto(nombre, sizeof(nombre), texto); }
};

// El unico registro de Partida.dat.
struct RegistroPartida {
    char nombreJugador[20] = "";
    int vidaActual = 6;
    int vidaMaxima = 6;
    int danio = 1;
    int velocidad = 3;
    int cantidadProyectiles = 1;
    int alcance = 6;
    int velocidadProyectil = 8;
    int cadencia = 400;
    bool vidaOculta = false;
    int salaActual = 1;
    bool salasCompletadas[10] = {false};
    int modificadores[20] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                             -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int puntaje = 0;
    bool finalizada = false;
    bool victoria = false;

    void setNombreJugador(const char* texto) { copiarTexto(nombreJugador, sizeof(nombreJugador), texto); }
};
