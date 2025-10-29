/**
 * @file     main.cpp
 * @brief    implementacion de las clases pendulo y sistema acoplado más su almacenamiento
 * @author   Angie Gomez, Leonardo Tovar
 * @date     29/10/25
 * @version  1.0
 * @license  owner
 */
#include "SistemaAcoplado.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <filesystem>
#include <limits>
#include <iomanip>
#include <vector>

int main() {
    namespace fs = std::filesystem;

    // ... (Lectura de parámetros del usuario es IGUAL) ...
    double L = 1.0, theta1_0 = 0.3, theta2_0 = 0.0, omega1_0 = 0.0, omega2_0 = 0.0, kappa = 1.0;
    double t_max = 20.0;
    double dt = 0.01;
    const double G = 9.81; 
    const double M = 1.0; // **MASA DE LOS PÉNDULOS (AÑADIDA)**

    std::cout << "\n=== Péndulos Acoplados con Interacción Cuadrática ===\n";
    std::cout << std::fixed << std::setprecision(4);

    // Parámetros físicos
    std::cout << "Longitud de la cuerda L (m) [Defecto: 1.0]: ";
    if (!(std::cin >> L) || L <= 0) { L = 1.0; }
    
    std::cout << "Constante de Acople Kappa [Defecto: 1.0]: ";
    if (!(std::cin >> kappa)) { kappa = 1.0; }
    std::cout << "Gravedad (g): " << G << " m/s^2, Masa (m): " << M << " kg\n";

    // Condiciones iniciales
    std::cout << "\n--- Condiciones Iniciales (Defectos: 0.3, 0.0, 0.0, 0.0) ---\n";
    std::cout << "Péndulo 1 (theta1) [Defecto: 0.3 rad]: ";
    if (!(std::cin >> theta1_0)) theta1_0 = 0.3;
    std::cout << "Péndulo 1 (omega1) [Defecto: 0.0 rad/s]: ";
    if (!(std::cin >> omega1_0)) omega1_0 = 0.0;

    std::cout << "Péndulo 2 (theta2) [Defecto: 0.0 rad]: ";
    if (!(std::cin >> theta2_0)) theta2_0 = 0.0;
    std::cout << "Péndulo 2 (omega2) [Defecto: 0.0 rad/s]: ";
    if (!(std::cin >> omega2_0)) omega2_0 = 0.0;
    
    // Parámetros de simulación
    std::cout << "\n--- Parámetros de Simulación (Defectos: 20.0, 0.01) ---\n";
    std::cout << "Tiempo máximo (t_max) [Defecto: 20.0]: ";
    if (!(std::cin >> t_max) || t_max <= 0) t_max = 20.0;
    std::cout << "Paso de tiempo (dt) [Defecto: 0.01]: ";
    if (!(std::cin >> dt) || dt <= 0) dt = 0.01;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // **CREACIÓN DE PÉNDULOS CON MASA**
    // Constructor usado: Pendulo(theta0, omega0, g, l, m)
    Pendulo p1(theta1_0, omega1_0, G, L, M); 
    Pendulo p2(theta2_0, omega2_0, G, L, M);

    // ... (El resto del código es IGUAL hasta el vector de apertura) ...
    SistemaAcoplado sistema(p1, p2, kappa);

    fs::path ruta_base = fs::current_path();
    std::cout << "\nDirectorio de ejecución: " << ruta_base << "\n";

    fs::path ruta_datos = "results/datos.dat";
    std::string ruta_datos_str = ruta_datos.string();

    std::cout << "Ruta de datos (absoluta esperada): " << fs::absolute(ruta_datos) << "\n";

    sistema.simular(t_max, dt, ruta_datos_str);

    if (fs::exists(ruta_datos)) {
        std::cout << "✅ Archivo de datos creado: " << ruta_datos << " ("
                  << fs::file_size(ruta_datos) << " bytes)\n";
    } else {
        std::cerr << "❌ El archivo de datos NO se creó.\n";
        return 1;
    }

    fs::path ruta_script = "scripts/plot_trayectorias.gp";
    if (!fs::exists(ruta_script)) {
        std::cerr << "\n⚠️ No se encontró el script de Gnuplot en: " << ruta_script << std::endl;
        return 1;
    }

    std::cout << "\nGenerando gráficos con Gnuplot..." << std::endl;
    std::string comando_gnuplot = "gnuplot \"" + ruta_script.string() + "\"";
    int status = system(comando_gnuplot.c_str());

    if (status == 0) {
        std::cout << "✅ Gráficos generados correctamente en 'results/' (¡Ahora incluye Energía!).\n";
        
        // --- ABRIR TODAS LAS GRÁFICAS (Vector Actualizado) ---
        std::vector<fs::path> rutas_graficas = {
            "results/trayectorias.png", 
            "results/theta1_vs_t.png",  
            "results/omega1_vs_t.png",  
            "results/theta2_vs_t.png",  
            "results/omega2_vs_t.png",  
            "results/modo_en_fase.png",    
            "results/modo_en_contrafase.png", 
            "results/transferencia_energia.png", // **NUEVA GRÁFICA**
            "results/conservacion_energia.png",  // **NUEVA GRÁFICA**
            "results/espacio_fase_animado.gif", 
            "results/pendulo_acoplado_movimiento.gif" 
        };
        std::string comando_abrir;

        std::cout << "Abriendo gráficas automáticamente...\n";
        
        for (const auto& ruta_grafica : rutas_graficas) {
            #ifdef _WIN32
                comando_abrir = "start \"" + ruta_grafica.string() + "\"";
            #elif __APPLE__
                comando_abrir = "open \"" + ruta_grafica.string() + "\"";
            #else
                comando_abrir = "xdg-open \"" + ruta_grafica.string() + "\"";
            #endif
            
            system(comando_abrir.c_str());
        }
        // ------------------------------------------

    } else {
        std::cerr << "❌ Error al ejecutar Gnuplot (Código de salida: " << status << ").\n";
    }

    // Ejecutar script de Python para Animación Física... (Se mantiene como estaba)
    fs::path ruta_script_py = "scripts/animacion_fisica.py";
    if (fs::exists(ruta_script_py)) {
        std::cout << "\nGenerando animación física con Python...\n";
        std::string comando_py = "python3 -u \"" + ruta_script_py.string() + "\"";
        int status_py = system(comando_py.c_str());
        if (status_py != 0) {
            std::cerr << "❌ Error al ejecutar el script de Python. (Código: " << status_py << ")\n";
        }
    } else {
        std::cerr << "\n⚠️ No se encontró el script de Python: " << ruta_script_py << std::endl;
    }
    
    return 0;
}
