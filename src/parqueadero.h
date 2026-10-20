
#ifndef PARQUEADERO_H
#define PARQUEADERO_H

#include <iostream>
#include <string>
#include <vector>
#include "Celda.h"

using namespace std;

class Parqueadero {
private:
    vector<Celda> Celdas;
    int capacidad;

public:
    Parqueadero(int capacidad_);

    int getCapacidad();
    int getOcupadas();
    int getDisponibles();

    bool ocuparCelda(string placa_);
    bool liberarCelda(string placa_);

    void mostrarEstado();
    void guardarEstado(string nombreArchivo);
};

#endif
