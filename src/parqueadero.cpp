
#include <iostream>
#include <fstream>
#include "parqueadero.h"

using namespace std;

Parqueadero::Parqueadero(int capacidad_) {
    if (capacidad_ < 1) {
        capacidad_ = 1;
    }

    capacidad = capacidad_;

    for (int i = 0; i < capacidad; i++) {
        Celda nueva(i + 1);
        Celdas.push_back(nueva);
    }
}

int Parqueadero::getCapacidad() {
    return capacidad;
}

int Parqueadero::getOcupadas() {
    int total = 0;

    for (int i = 0; i < capacidad; i++) {
        if (Celdas[i].getOcupada()) {
            total++;
        }
    }

    return total;
}

int Parqueadero::getDisponibles() {
    return capacidad - getOcupadas();
}

bool Parqueadero::ocuparCelda(string placa_) {
    for (int i = 0; i < capacidad; i++) {
        if (!Celdas[i].getOcupada()) {
            Celdas[i].ocupar(placa_);
            return true;
        }
    }

    return false;
}

bool Parqueadero::liberarCelda(string placa_) {
    for (int i = 0; i < capacidad; i++) {
        if (Celdas[i].getOcupada() &&
            Celdas[i].getPlaca() == placa_) {
            Celdas[i].liberar();
            return true;
        }
    }

    return false;
}

void Parqueadero::mostrarEstado() {
    cout << "\n--- ESTADO DEL PARQUEADERO ---" << endl;

    for (int i = 0; i < capacidad; i++) {
        cout << "Celda " << Celdas[i].getNumero();

        if (Celdas[i].getOcupada()) {
            cout << " | OCUPADA | " << Celdas[i].getPlaca()
                 << " | Entrada: " << Celdas[i].getHoraEntrada();
        } else {
            cout << " | LIBRE";
        }

        cout << endl;
    }

    cout << "Capacidad: " << getCapacidad() << endl;
    cout << "Ocupadas: " << getOcupadas() << endl;
    cout << "Disponibles: " << getDisponibles() << endl;
}

void Parqueadero::guardarEstado(string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo guardar el estado del parqueadero." << endl;
        return;
    }

    archivo << "Capacidad: " << getCapacidad() << "\n";
    archivo << "Ocupadas: " << getOcupadas() << "\n";
    archivo << "Disponibles: " << getDisponibles() << "\n";
    archivo << "-------------------------\n";

    for (int i = 0; i < capacidad; i++) {
        archivo << "Celda " << Celdas[i].getNumero();

        if (Celdas[i].getOcupada()) {
            archivo << " | OCUPADA"
                    << " | Placa: " << Celdas[i].getPlaca()
                    << " | Entrada: " << Celdas[i].getHoraEntrada();
        } else {
            archivo << " | LIBRE";
        }

        archivo << "\n";
    }
}
