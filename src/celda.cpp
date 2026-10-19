#include "Celda.h"

Celda::Celda(int numero_) {
    numero = numero_;
    ocupada = false;
    placa = "";
}

int Celda::getNumero() {
    return numero;
}

bool Celda::getOcupada() {
    return ocupada;
}

string Celda::getPlaca() {
    return placa;
}

void Celda::ocupar(string placa_) {
    placa = placa_;
    ocupada = true;
}

void Celda::liberar() {
    placa = "";
    ocupada = false;
}