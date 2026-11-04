#pragma once

// Representacion de una fila de Salas.dat.
// Se completa a futuro con los otros registros binarios.
struct RegistroSala {
    int idSala = 0;
    int tipo = 0;
    int salaNorte = -1;
    int salaSur = -1;
    int salaEste = -1;
    int salaOeste = -1;
    bool opcional = false;
};
