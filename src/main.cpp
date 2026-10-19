#include <iostream>
#include "Placa.h"

using namespace std;

int main() {
    Placa placa1("ABC123");

    cout << "Placa del vehiculo: " << placa1.getID() << endl;

    return 0;
}