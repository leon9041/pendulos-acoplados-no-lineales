# PÉNDULOS ACOPLADOS NO LINEALES

## Título del Proyecto

**`pendulos-acoplados-no-lineales`**

Simulación numérica de péndulos acoplados con interacción no lineal cuadrática. Este proyecto implementa la solución de las EDOs acopladas mediante un integrador numérico para analizar la transferencia de energía y los modos de oscilación del sistema.

***

## Ecuaciones del Sistema

El sistema modela la dinámica angular $\theta_1$ y $\theta_2$ de dos péndulos bajo gravedad y acoplamiento cuadrático:

* **Péndulo 1:** $\ddot{\theta}_1 + \frac{g}{l} \sin \theta_1 + \kappa(\theta_1 - \theta_2)^2 = 0$
* **Péndulo 2:** $\ddot{\theta}_2 + \frac{g}{l} \sin \theta_2 + \kappa(\theta_2 - \theta_1)^2 = 0$

***

## Requisitos del Sistema

Para compilar y ejecutar el proyecto, se necesita:

1.  **Compilador C++:** Soporte para **C++17** (e.g., GCC/G++ v9.x o superior).
2.  **Make:** Utilidad `make` para el proceso de compilación.
3.  **Gnuplot:** Para la generación de gráficas estáticas (`.png`) y animaciones de espacio fase.
4.  **Python 3:** Con la librería `matplotlib` para la animación física del movimiento.

***

## Compilación y Ejecución

El proyecto utiliza un `Makefile` para automatizar la compilación, la ejecución de la simulación y la generación de gráficos.

### 1. Compilación

Compila el ejecutable principal (`simulador`) desde la raíz del proyecto:

```bash
make

## Estructura del Código
El código sigue la siguiente estructura mínima requerida para el proyecto:

pendulos-acoplados-no-lineales/
├── include/           # Cabeceras (.h) de clases (Pendulo.h, SistemaAcoplado.h)
├── src/               # Implementación de clases y main.cpp
├── scripts/           # Scripts de Gnuplot (.gp) y Python (.py)
├── results/           # Archivos de salida (datos.dat, .png, .gif)
├── documents/         # Análisis físico (LaTeX) y Diagrama de Flujo
├── Makefile
└── README.md          # Este archivo
