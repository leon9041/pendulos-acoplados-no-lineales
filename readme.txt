PROYECTO: PÉNDULOS ACOPLADOS NO LINEALES

DESCRIPCIÓN:
Simulación de péndulos acoplados con interacción no lineal cuadrática. El proyecto analiza la transferencia de energía y los modos de oscilación del sistema, resolviendo las EDOs acopladas.

EJECUCIÓN:
El programa requiere la compilación previa con Make (make).
Una vez compilado, se ejecuta usando el nombre del ejecutable:

./pendulos

El programa solicitará interactivamente las condiciones iniciales y los parámetros de la simulación.

ESTRUCTURA DE CARPETAS MÍNIMA:
include/           - Cabeceras (.h) de clases.
src/               - Implementación de clases y main.cpp.
scripts/           - Scripts de Gnuplot (.gp) y Python (.py) para gráficas y animaciones.
results/           - Archivos de salida (datos.dat, .png, .gif).
documents/         - Análisis físico (LaTeX) y Diagrama de Flujo.
Makefile           - Archivo de compilación.
README.md          - Este documento.
