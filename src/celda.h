
#ifndef CELDA_H
#define CELDA_H

#include <string>
using namespace std;

class Celda {
private:
    int numero;
    bool ocupada;
    string placa;
    string horaEntrada;

public:
    Celda(int numero_);

    int getNumero();
    bool getOcupada();
    string getPlaca();
    string getHoraEntrada();

    void ocupar(string placa_);
    void liberar();
};

#endif
