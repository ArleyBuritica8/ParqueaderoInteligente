
import ctypes
import tkinter as tk
from pathlib import Path

# Buscar la DLL en la carpeta raiz del proyecto.
BASE_DIR = Path(__file__).resolve().parent.parent
DLL_PATH = BASE_DIR / "parqueadero.dll"

biblioteca = ctypes.CDLL(str(DLL_PATH))

biblioteca.obtener_estado.argtypes = [
    ctypes.POINTER(ctypes.c_char),
    ctypes.c_int
]
biblioteca.obtener_estado.restype = ctypes.c_int


def obtener_estado():
    buffer = ctypes.create_string_buffer(16384)
    resultado = biblioteca.obtener_estado(buffer, len(buffer))

    if resultado < 0:
        return None

    return buffer.value.decode("utf-8")


def leer_celdas(contenido):
    celdas = []

    for linea in contenido.splitlines():
        linea = linea.strip()

        if not linea.startswith("Celda "):
            continue

        partes = linea.split("|")
        numero = partes[0].replace("Celda", "").strip()

        if len(partes) < 2:
            continue

        estado = partes[1].strip()
        placa = ""
        hora = ""

        for parte in partes[2:]:
            parte = parte.strip()

            if parte.startswith("Placa:"):
                placa = parte.replace("Placa:", "", 1).strip()
            elif parte.startswith("Entrada:"):
                hora = parte.replace("Entrada:", "", 1).strip()

        celdas.append({
            "numero": numero,
            "estado": estado,
            "placa": placa,
            "hora": hora
        })

    return celdas


def actualizar_interfaz():
    contenido = obtener_estado()

    if contenido is None:
        estado_general.config(
            text="No se pudo leer el estado del parqueadero."
        )
        ventana.after(2000, actualizar_interfaz)
        return

    datos = {}

    for linea in contenido.splitlines():
        if ":" in linea and not linea.startswith("Celda "):
            clave, valor = linea.split(":", 1)
            datos[clave.strip()] = valor.strip()

    capacidad = datos.get("Capacidad", "0")
    ocupadas = datos.get("Ocupadas", "0")
    disponibles = datos.get("Disponibles", "0")

    resumen.config(
        text=f"Capacidad: {capacidad}    "
             f"Ocupadas: {ocupadas}    "
             f"Disponibles: {disponibles}"
    )

    for widget in panel_celdas.winfo_children():
        widget.destroy()

    celdas = leer_celdas(contenido)
    columnas = 3

    for indice, celda in enumerate(celdas):
        ocupada = celda["estado"] == "OCUPADA"
        color = "#F8D7DA" if ocupada else "#D1E7DD"
        texto_estado = "OCUPADA" if ocupada else "LIBRE"

        tarjeta = tk.Frame(
            panel_celdas,
            bg=color,
            bd=1,
            relief="solid",
            padx=12,
            pady=10
        )

        tarjeta.grid(
            row=indice // columnas,
            column=indice % columnas,
            padx=8,
            pady=8,
            sticky="nsew"
        )

        tk.Label(
            tarjeta,
            text=f"Celda {celda['numero']}",
            font=("Arial", 12, "bold"),
            bg=color
        ).pack(anchor="w")

        tk.Label(
            tarjeta,
            text=texto_estado,
            font=("Arial", 10, "bold"),
            bg=color
        ).pack(anchor="w", pady=(4, 0))

        if ocupada:
            tk.Label(
                tarjeta,
                text=f"Placa: {celda['placa']}",
                font=("Arial", 10),
                bg=color
            ).pack(anchor="w", pady=(4, 0))

            tk.Label(
                tarjeta,
                text=f"Entrada: {celda['hora']}",
                font=("Arial", 9),
                bg=color
            ).pack(anchor="w", pady=(2, 0))

    for columna in range(columnas):
        panel_celdas.grid_columnconfigure(
            columna, weight=1
        )

    estado_general.config(text="Estado actualizado desde la DLL.")

    # Consultar nuevamente cada 2 segundos.
    ventana.after(2000, actualizar_interfaz)


ventana = tk.Tk()
ventana.title("Parqueadero Inteligente")
ventana.geometry("850x650")
ventana.minsize(600, 400)

titulo = tk.Label(
    ventana,
    text="PARQUEADERO INTELIGENTE",
    font=("Arial", 20, "bold")
)
titulo.pack(pady=(18, 8))

resumen = tk.Label(
    ventana,
    text="Consultando estado...",
    font=("Arial", 12)
)
resumen.pack(pady=8)

separador = tk.Frame(ventana, height=2, bg="#BBBBBB")
separador.pack(fill="x", padx=20, pady=8)

panel_celdas = tk.Frame(ventana)
panel_celdas.pack(fill="both", expand=True, padx=12, pady=8)

estado_general = tk.Label(
    ventana,
    text="",
    font=("Arial", 9)
)
estado_general.pack(pady=(4, 12))

actualizar_interfaz()
ventana.mainloop()

