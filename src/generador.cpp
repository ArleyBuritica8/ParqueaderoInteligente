#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    WSADATA datos;
    SOCKET conexion;
    sockaddr_in direccion;

    if (WSAStartup(MAKEWORD(2, 2), &datos) != 0) {
        cout << "Error al iniciar Winsock." << endl;
        return 1;
    }

    conexion = socket(AF_INET, SOCK_STREAM, 0);

    if (conexion == INVALID_SOCKET) {
        cout << "Error al crear el socket." << endl;
        WSACleanup();
        return 1;
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = inet_addr("127.0.0.1");
    direccion.sin_port = htons(54000);

    cout << "Conectando con el servidor..." << endl;

    if (connect(conexion, (sockaddr*)&direccion,
                sizeof(direccion)) == SOCKET_ERROR) {
        cout << "No se pudo conectar al servidor." << endl;
        closesocket(conexion);
        WSACleanup();
        return 1;
    }

    cout << "Conexion establecida correctamente." << endl;

    string placas[] = {
        "ABC123",
        "XYZ789",
        "DEF456",
        "ABC123",
        "GHI321"
    };

    for (int i = 0; i < 5; i++) {
        string mensaje = placas[i] + "\n";

        int resultado = send(conexion, mensaje.c_str(),
                             mensaje.size(), 0);

        if (resultado == SOCKET_ERROR) {
            cout << "Error al enviar la placa." << endl;
            break;
        }

        cout << "Placa enviada: " << placas[i] << endl;

        this_thread::sleep_for(chrono::seconds(2));
    }

    closesocket(conexion);
    WSACleanup();

    cout << "Generador finalizado." << endl;

    return 0;
}
