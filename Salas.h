#pragma once



class Salas
{
private:
    int _idSala;
    int _tipo;
    int _idEnemigo;
    int _idRecompensa;
    bool _completada;

public:
    Salas();

    void setIdSala(int id);
    int getIdSala();
    void setTipo(int tipo);
    int getTipo();
    void setIdEnemigo(int id);
    int getIdEnemigo();
    void setIdRecompensa(int id);
    int getIdRecompensa();



protected:


};



