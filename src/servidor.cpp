
#include <iostream>
#include <winsock2.h>
#include <string>
#include "parqueadero.h"

using namespace std;

int main() {
    WSADATA datos;
    SOCKET servidor;
    SOCKET cliente;
    sockaddr_in direccion;

    int capacidad;

    cout << "=== PARQUEADERO INTELIGENTE ===" << endl;
    cout << "Cuantas celdas tendra el parqueadero? ";

    if (!(cin >> capacidad) || capacidad < 1 || capacidad > 1000) {
        cerr << "Ingresa una capacidad entre 1 y 1000." << endl;
        return 1;
    }

    Parqueadero parqueadero(capacidad);

    parqueadero.guardarEstado("estado_parqueadero.txt");

    if (WSAStartup(MAKEWORD(2, 2), &datos) != 0) {
        cerr << "Error al iniciar Winsock." << endl;
        return 1;
    }

    servidor = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor == INVALID_SOCKET) {
        cerr << "Error al crear el socket." << endl;
        WSACleanup();
        return 1;
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(54000);

    if (bind(servidor, (sockaddr*)&direccion,
             sizeof(direccion)) == SOCKET_ERROR) {
        cerr << "Error al asociar el puerto 54000." << endl;
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    if (listen(servidor, 1) == SOCKET_ERROR) {
        cerr << "Error al esperar conexiones." << endl;
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    cout << "\nParqueadero creado correctamente." << endl;
    parqueadero.mostrarEstado();

    cout << "\nServidor iniciado en el puerto 54000." << endl;
    cout << "Esperando al generador..." << endl;

    cliente = accept(servidor, nullptr, nullptr);

    if (cliente == INVALID_SOCKET) {
        cerr << "Error al aceptar la conexion." << endl;
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    cout << "Generador conectado correctamente." << endl;

    char buffer[1024];
    string pendiente;
    int bytesRecibidos;

    while ((bytesRecibidos = recv(
                cliente, buffer, sizeof(buffer), 0)) > 0) {

        pendiente.append(buffer, bytesRecibidos);

        size_t posicion;

        while ((posicion = pendiente.find('\n')) != string::npos) {
            string placa = pendiente.substr(0, posicion);
            pendiente.erase(0, posicion + 1);

            if (!placa.empty() && placa.back() == '\r') {
                placa.pop_back();
            }

            if (placa.empty()) {
                continue;
            }

            cout << "\nPlaca recibida: " << placa << endl;

            if (parqueadero.liberarCelda(placa)) {
                cout << "Salida: " << placa << endl;
            } else if (parqueadero.ocuparCelda(placa)) {
                cout << "Entrada: " << placa << endl;
            } else {
                cout << "Parqueadero lleno. No se pudo asignar "
                     << placa << "." << endl;
            }

            parqueadero.guardarEstado("estado_parqueadero.txt");
            parqueadero.mostrarEstado();
        }
    }

    cout << "\nConexion finalizada." << endl;

    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();

    return 0;
}
