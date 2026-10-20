# Parqueadero Inteligente

## Descripción

Parqueadero Inteligente es un sistema desarrollado en C++ y Python que permite simular la entrada y salida de vehículos de un parqueadero mediante el envío de placas a través de sockets TCP.

El sistema asigna una celda disponible a cada vehículo, registra su hora de entrada y libera la celda cuando recibe nuevamente la misma placa. La información se visualiza mediante una interfaz gráfica desarrollada en Python que consulta una biblioteca dinámica.

## Objetivos

- Implementar la comunicación entre procesos mediante sockets TCP.
- Gestionar las celdas ocupadas y disponibles.
- Registrar las placas y las horas de entrada.
- Utilizar una biblioteca dinámica para consultar el estado del parqueadero.
- Representar gráficamente el estado de cada celda.

## Tecnologías utilizadas

- **C++:** implementación del generador, servidor y clases del parqueadero.
- **Winsock:** comunicación TCP entre el generador y el servidor en Windows.
- **Python:** desarrollo de la interfaz gráfica.
- **Tkinter:** presentación visual de las celdas.
- **ctypes:** acceso a la biblioteca dinámica desde Python.
- **Git y GitHub:** control de versiones y almacenamiento del proyecto.

## Arquitectura del sistema

El sistema está compuesto por los siguientes elementos:

1. **Generador de placas (C++):** envía las placas al servidor cada dos segundos.
2. **Servidor (C++):** recibe las placas mediante un socket TCP, asigna las celdas, registra las horas y procesa las salidas.
3. **Biblioteca dinámica:** permite que Python consulte la información guardada por el servidor.
4. **Visualizador (Python):** muestra las celdas ocupadas y libres, las placas y las horas de entrada.

## Funcionamiento

- Al iniciar el servidor, el usuario selecciona la capacidad del parqueadero.
- Cuando llega una placa nueva, se asigna la primera celda disponible.
- Se registra la hora de entrada del vehículo.
- Cuando se recibe nuevamente una placa que está estacionada, se libera su celda.
- El estado del parqueadero se guarda en `estado_parqueadero.txt`.
- El visualizador consulta la información mediante la biblioteca dinámica y actualiza la interfaz gráfica.

## Estructura del proyecto

```text
ParqueaderoInteligente/
├── Biblioteca/
│   └── estado_api.cpp
├── src/
│   ├── placa.h
│   ├── placa.cpp
│   ├── celda.h
│   ├── celda.cpp
│   ├── parqueadero.h
│   ├── parqueadero.cpp
│   ├── generador.cpp
│   ├── servidor.cpp
│   └── main.cpp
├── visualizador/
│   └── visualizador.py
├── .gitignore
└── README.md
```

## Requisitos

- Windows.
- Compilador g++ compatible con Winsock.
- Python 3 instalado.
- Git, si se desea clonar el repositorio.

## Compilación

Ejecutar los siguientes comandos desde la carpeta raíz del proyecto:

### 1. Compilar el servidor

```powershell
g++ src/servidor.cpp src/parqueadero.cpp src/celda.cpp -o servidor.exe -lws2_32
```

### 2. Compilar el generador

```powershell
g++ src/generador.cpp -o generador.exe -lws2_32
```

### 3. Compilar la biblioteca dinámica

```powershell
g++ -shared -static -o parqueadero.dll Biblioteca/estado_api.cpp
```

## Ejecución

Abrir tres terminales desde la carpeta raíz del proyecto.

**Terminal 1: visualizador**

```powershell
python visualizador/visualizador.py
```

**Terminal 2: servidor**

```powershell
.\servidor.exe
```

Ingresar la cantidad de celdas cuando el programa lo solicite y esperar la conexión.

**Terminal 3: generador**

```powershell
.\generador.exe
```

El generador se conecta al servidor y envía las placas de prueba. La interfaz gráfica muestra el estado del parqueadero.

## Diagramas

En esta sección se incorporarán los diagramas UML de clases y de arquitectura del sistema.

## Autor

Proyecto académico de Parqueadero Inteligente.
