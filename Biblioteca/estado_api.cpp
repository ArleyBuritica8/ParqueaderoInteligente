#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Funcion publica que Python podra llamar mediante la DLL.
extern "C" __declspec(dllexport)
int __cdecl obtener_estado(char* buffer, int tamano) {

    if (buffer == nullptr || tamano <= 0) {
        return -1;
    }

    ifstream archivo("estado_parqueadero.txt");

    if (!archivo.is_open()) {
        return -1;
    }

    string contenido(
        (istreambuf_iterator<char>(archivo)),
        istreambuf_iterator<char>()
    );

    if (contenido.size() + 1 > static_cast<size_t>(tamano)) {
        return -2;
    }

    memcpy(buffer, contenido.c_str(), contenido.size() + 1);

    return static_cast<int>(contenido.size());
}