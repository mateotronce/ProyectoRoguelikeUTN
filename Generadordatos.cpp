#include "Generadordatos.h"
#include "Archivo.h"
#include "Registros.h"

//  funciones auxiliares para no repetir los campos

RegistroSala crearSala(int id, int tipo, int norte, int sur, int este, int oeste, bool opcional)
{
    RegistroSala r;
    r.idSala = id;
    r.tipo = tipo;
    r.salaNorte = norte;
    r.salaSur = sur;
    r.salaEste = este;
    r.salaOeste = oeste;
    r.opcional = opcional;
    return r;
}

RegistroSalaEnemigo crearSalaEnemigo(int idSala, int idEnemigo, int cantidad)
{
    RegistroSalaEnemigo r;
    r.idSala = idSala;
    r.idEnemigo = idEnemigo;
    r.cantidad = cantidad;
    return r;
}

RegistroEnemigo crearEnemigo(int id, const char* nombre, int tipo, int vida,
                                    int danio, int velocidad, int cadencia, int puntos)
{
    RegistroEnemigo r;
    r.idEnemigo = id;
    r.setNombre(nombre);
    r.tipo = tipo;
    r.vida = vida;
    r.danio = danio;
    r.velocidad = velocidad;
    r.cadenciaDisparo = cadencia;
    r.puntos = puntos;
    return r;
}

RegistroModificador crearModificador(int id, const char* nombre, bool maldicion,
                                            int atr1, int val1, int atr2, int val2)
{
    RegistroModificador r;
    r.idModificador = id;
    r.setNombre(nombre);
    r.esMaldicion = maldicion;
    r.atributo1 = atr1;
    r.valor1 = val1;
    r.atributo2 = atr2;
    r.valor2 = val2;
    return r;
}

RegistroRecompensa crearRecompensa(int id, int idSala, const char* nombre,
                                          int idMejora, int mult, int idMaldicion)
{
    RegistroRecompensa r;
    r.idRecompensa = id;
    r.idSala = idSala;
    r.setNombre(nombre);
    r.idMejora = idMejora;
    r.multiplicador = mult;
    r.idMaldicion = idMaldicion;
    return r;
}

//  datos

bool generarDatosIniciales()
{
    bool ok = true;

    //  Salas.dat
    // tipo: 1 inicio, 2 combate, 3 tesoro, 4 altar maldito, 5 final

    Archivo<RegistroSala> archSalas("data/Salas.dat");
    archSalas.vaciar();
    //                               id tipo N   S   E   O  opcional
    ok = archSalas.guardar(crearSala( 1, 1, -1, -1,  2, -1, false)) && ok;
    ok = archSalas.guardar(crearSala( 2, 2,  3, -1,  5,  1, false)) && ok;
    ok = archSalas.guardar(crearSala( 3, 2,  4,  2, -1, -1, true))  && ok;
    ok = archSalas.guardar(crearSala( 4, 4, -1,  3, -1, -1, true))  && ok;
    ok = archSalas.guardar(crearSala( 5, 2, -1,  6,  7,  2, false)) && ok;
    ok = archSalas.guardar(crearSala( 6, 3,  5, -1, -1, -1, true))  && ok;
    ok = archSalas.guardar(crearSala( 7, 2,  8, -1,  9,  5, false)) && ok;
    ok = archSalas.guardar(crearSala( 8, 4, -1,  7, -1, -1, true))  && ok;
    ok = archSalas.guardar(crearSala( 9, 2, -1, -1, 10,  7, false)) && ok;
    ok = archSalas.guardar(crearSala(10, 5, -1, -1, -1,  9, false)) && ok;

    //  Enemigos.dat
    Archivo<RegistroEnemigo> archEnemigos("data/Enemigos.dat");
    archEnemigos.vaciar();
    //                                     id nombre    tipo vida danio vel cadencia puntos
    ok = archEnemigos.guardar(crearEnemigo(1, "Acolito",   1, 4, 1, 2,    0, 10)) && ok;
    ok = archEnemigos.guardar(crearEnemigo(2, "Hechicero", 2, 2, 1, 1, 2000, 15)) && ok;
    ok = archEnemigos.guardar(crearEnemigo(3, "Guardian",  3, 8, 2, 1,    0, 25)) && ok;

    //  SalaEnemigos.dat  (1 Acolito, 2 Hechicero, 3 Guardian)
    Archivo<RegistroSalaEnemigo> archSE("data/SalaEnemigos.dat");
    archSE.vaciar();
    //                                  sala enemigo cantidad
    ok = archSE.guardar(crearSalaEnemigo( 2, 1, 3)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 3, 1, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 3, 2, 1)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 5, 1, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 5, 2, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 7, 3, 1)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 7, 1, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 9, 3, 1)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 9, 2, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo( 9, 1, 1)) && ok;
    ok = archSE.guardar(crearSalaEnemigo(10, 3, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo(10, 1, 2)) && ok;
    ok = archSE.guardar(crearSalaEnemigo(10, 2, 1)) && ok;

    //  Modificadores.dat
    // atributos: 1 vida max, 2 danio, 3 velocidad, 4 proyectiles, 5 alcance,
    //            6 cadencia, 7 vida oculta, 8 vida actual, 9 vel. proyectil
    // "valor" es el cambio que se SUMA al atributo (negativo = resta)
    Archivo<RegistroModificador> archMod("data/Modificadores.dat");
    archMod.vaciar();
    //                                    id  nombre                     maldicion atr1 val1 atr2 val2
    ok = archMod.guardar(crearModificador( 1, "Mejora de vida",           false, 1,   1, 8,  1)) && ok;
    ok = archMod.guardar(crearModificador( 2, "Mejora de danio",          false, 2,   1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 3, "Mejora de velocidad",      false, 3,   1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 4, "Mejora de proyectiles",    false, 4,   1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 5, "Mejora de alcance",        false, 5,   2, 9,  2)) && ok;
    ok = archMod.guardar(crearModificador( 6, "Maldicion de lentitud",    true,  3,  -1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 7, "Maldicion de vida",        true,  1,  -1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 8, "Maldicion de cadencia",    true,  6, 200, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador( 9, "Maldicion de vida oculta", true,  7,   1, 0,  0)) && ok;
    ok = archMod.guardar(crearModificador(10, "Maldicion de debilidad",   true,  2,  -1, 0,  0)) && ok;

    //  Recompensas.dat
    Archivo<RegistroRecompensa> archRec("data/Recompensas.dat");
    archRec.vaciar();
    //                                    id sala nombre               mejora mult maldicion
    ok = archRec.guardar(crearRecompensa( 1, 2, "Mejora de danio",        2, 1, -1)) && ok;
    ok = archRec.guardar(crearRecompensa( 2, 3, "Mejora de alcance",      5, 1, -1)) && ok;
    ok = archRec.guardar(crearRecompensa( 3, 4, "Rosario de hueso",       4, 2,  6)) && ok;
    ok = archRec.guardar(crearRecompensa( 4, 4, "Ojo de vidrio",          5, 2,  9)) && ok;
    ok = archRec.guardar(crearRecompensa( 5, 5, "Mejora de velocidad",    3, 1, -1)) && ok;
    ok = archRec.guardar(crearRecompensa( 6, 6, "Mejora de vida",         1, 1, -1)) && ok;
    ok = archRec.guardar(crearRecompensa( 7, 7, "Mejora de vida",         1, 1, -1)) && ok;
    ok = archRec.guardar(crearRecompensa( 8, 8, "Espada de la secta",     2, 2,  7)) && ok;
    ok = archRec.guardar(crearRecompensa( 9, 8, "Caliz agrietado",        1, 2,  8)) && ok;
    ok = archRec.guardar(crearRecompensa(10, 8, "Botas del penitente",    3, 2, 10)) && ok;
    ok = archRec.guardar(crearRecompensa(11, 9, "Mejora de proyectiles",  4, 1, -1)) && ok;

    return ok;
}
