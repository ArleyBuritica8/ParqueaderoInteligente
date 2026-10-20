#include <iostream>
#include "parqueadero.h"

using namespace std;

int main() {
    int capacidad = 10;

    cout << "=== PARQUEADERO INTELIGENTE ===" << endl;

    Parqueadero parqueadero(capacidad);

    cout << "Parqueadero creado con "
         << capacidad << " celdas." << endl;

    cout << "\n--- ENTRADA DE VEHICULOS ---" << endl;

    parqueadero.ocuparCelda("ABC123");
    parqueadero.mostrarEstado();

    parqueadero.ocuparCelda("XYZ789");
    parqueadero.mostrarEstado();

    cout << "\n--- SALIDA DE VEHICULO ---" << endl;

    parqueadero.liberarCelda("ABC123");
    parqueadero.mostrarEstado();

    return 0;
}