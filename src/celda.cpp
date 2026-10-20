
#include "Celda.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Celda::Celda(int numero_) {
    numero = numero_;
    ocupada = false;
    placa = "";
    horaEntrada = "";
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

string Celda::getHoraEntrada() {
    return horaEntrada;
}

void Celda::ocupar(string placa_) {
    placa = placa_;
    ocupada = true;

    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);

    if (tiempoLocal != nullptr) {
        ostringstream salida;
        salida << put_time(tiempoLocal, "%Y-%m-%d %H:%M:%S");
        horaEntrada = salida.str();
    } else {
        horaEntrada = "Hora no disponible";
    }
}

void Celda::liberar() {
    placa = "";
    horaEntrada = "";
    ocupada = false;
}
