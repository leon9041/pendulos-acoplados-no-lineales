/**
 * @file     TorpedoCarrito.cpp
 * @brief    Simulacion de persecucion entre un torpedo y un carrito en movimiento
 * @author   Angie Gomez, Leonardo Tovar
 * @date     29/10/25
 * @version  1.0
 * @license  owner
 */

#include "SistemaAcoplado.h"
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <cmath>
#include <fstream>

SistemaAcoplado::SistemaAcoplado(Pendulo p1_, Pendulo p2_, double kappa_)
    : p1(p1_), p2(p2_), kappa(kappa_) {}

// **NUEVO MÉTODO:** Calcula la energía de un péndulo individual (incluida la potencial de acople)
// Se podría optimizar, pero por claridad, calculamos KE y PE por separado.
double SistemaAcoplado::energia_pendulo(const Pendulo& p, const Pendulo& otro) const {
    // KE = 1/2 * m * l^2 * omega^2
    double ke = 0.5 * p.m * p.l * p.l * p.omega * p.omega;
    
    // PE Gravitacional = m * g * l * (1 - cos(theta))
    double pe_grav = p.m * p.g * p.l * (1.0 - std::cos(p.theta));
    
    // PE Acoplamiento = 1/2 * kappa * (theta1 - theta2)^2 (Esta es la energía del sistema)
    // Para atribuir a un péndulo, usamos la mitad del término de acoplamiento.
    // Opcional, aquí solo contabilizaremos la energía individual (KE + PE_grav).
    // Para simplificar el análisis de *transferencia*, solo exportaremos KE+PE_grav.

    // Transferencia se ve mejor con KE individual
    return ke + pe_grav;
}

// **NUEVO MÉTODO:** Calcula la energía cinética (KE)
double SistemaAcoplado::ke(const Pendulo& p) const {
    return 0.5 * p.m * p.l * p.l * p.omega * p.omega;
}

// **NUEVO MÉTODO:** Calcula la energía potencial (PE) (Gravitacional)
double SistemaAcoplado::pe_grav(const Pendulo& p) const {
    return p.m * p.g * p.l * (1.0 - std::cos(p.theta));
}

// **NUEVO MÉTODO:** Calcula la energía Potencial de acoplamiento (PE_acople)
double SistemaAcoplado::pe_acople() const {
    return 0.5 * kappa * std::pow(p1.theta - p2.theta, 2);
}

// **NUEVO MÉTODO:** Calcula la Energía Total (KE1 + KE2 + PE_Grav1 + PE_Grav2 + PE_Acople)
double SistemaAcoplado::energia_total() const {
    return ke(p1) + ke(p2) + pe_grav(p1) + pe_grav(p2) + pe_acople();
}


void SistemaAcoplado::paso_rk4(double dt) {
    // ... (El cuerpo de paso_rk4 es IGUAL, la masa NO afecta la aceleración) ...
    auto f1 = [&](double theta1, double theta2){
        return - (p1.g/p1.l) * std::sin(theta1) - kappa * std::pow(theta1 - theta2, 2);
    };

    auto f2 = [&](double theta1, double theta2){
        return - (p2.g/p2.l) * std::sin(theta2) - kappa * std::pow(theta2 - theta1, 2);
    };

    auto g1 = [&](double omega1){ return omega1; };
    auto g2 = [&](double omega2){ return omega2; };

    // === PENDIENTE 1 (K1) ===
    double k1_theta1 = g1(p1.omega);
    double k1_omega1 = f1(p1.theta, p2.theta);
    double k1_theta2 = g2(p2.omega);
    double k1_omega2 = f2(p1.theta, p2.theta);

    // === PENDIENTE 2 (K2) ===
    double k2_theta1 = g1(p1.omega + 0.5*dt*k1_omega1);
    double k2_omega1 = f1(p1.theta + 0.5*dt*k1_theta1, p2.theta + 0.5*dt*k1_theta2);
    double k2_theta2 = g2(p2.omega + 0.5*dt*k1_omega2);
    double k2_omega2 = f2(p1.theta + 0.5*dt*k1_theta1, p2.theta + 0.5*dt*k1_theta2);

    // === PENDIENTE 3 (K3) ===
    double k3_theta1 = g1(p1.omega + 0.5*dt*k2_omega1);
    double k3_omega1 = f1(p1.theta + 0.5*dt*k2_theta1, p2.theta + 0.5*dt*k2_theta2);
    double k3_theta2 = g2(p2.omega + 0.5*dt*k2_omega2);
    double k3_omega2 = f2(p1.theta + 0.5*dt*k2_theta1, p2.theta + 0.5*dt*k2_theta2);

    // === PENDIENTE 4 (K4) ===
    double k4_theta1 = g1(p1.omega + dt*k3_omega1);
    double k4_omega1 = f1(p1.theta + dt*k3_theta1, p2.theta + dt*k3_theta2);
    double k4_theta2 = g2(p2.omega + dt*k3_omega2);
    double k4_omega2 = f2(p1.theta + dt*k3_theta1, p2.theta + dt*k3_theta2);

    // Actualización de estado (RK4 completo para las 4 variables)
    p1.theta += (dt/6.0) * (k1_theta1 + 2*k2_theta1 + 2*k3_theta1 + k4_theta1);
    p1.omega += (dt/6.0) * (k1_omega1 + 2*k2_omega1 + 2*k3_omega1 + k4_omega1);

    p2.theta += (dt/6.0) * (k1_theta2 + 2*k2_theta2 + 2*k3_theta2 + k4_theta2);
    p2.omega += (dt/6.0) * (k1_omega2 + 2*k2_omega2 + 2*k3_omega2 + k4_omega2);
}

void SistemaAcoplado::simular(double tmax, double dt, const std::string& filename) {
    namespace fs = std::filesystem;

    fs::path ruta = filename; 
    fs::path carpeta = ruta.parent_path();
    
    if (!carpeta.empty() && !fs::exists(carpeta)) {
        try {
            std::cout << "Intentando crear directorio: " << carpeta << std::endl;
            fs::create_directories(carpeta);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "❌ Error crítico creando carpeta " << carpeta << ": " << e.what() << std::endl;
            return; 
        }
    }

    std::ofstream file(ruta);
    if (!file.is_open()) {
        std::cerr << "❌ Error crítico: no se pudo abrir/crear el fichero de salida: " << fs::absolute(ruta) << std::endl;
        return;
    }

    // **CABECERA MODIFICADA: AÑADE COLUMNAS DE ENERGÍA**
    file << "# t theta1 omega1 theta2 omega2 KE1 PE1 KE2 PE2 E_Total\n";
    file << std::fixed << std::setprecision(8);

    double t = 0.0;
    
    // Función auxiliar para escribir una línea de datos
    auto escribir_datos = [&](double tiempo) {
        file << tiempo << " "
             << p1.theta << " " << p1.omega << " "
             << p2.theta << " " << p2.omega << " "
             // Nuevas columnas de energía
             << ke(p1) << " " << pe_grav(p1) << " "
             << ke(p2) << " " << pe_grav(p2) << " "
             << energia_total() << "\n";
    };

    escribir_datos(t);

    while (t < tmax) {
        paso_rk4(dt);
        t += dt;
        escribir_datos(t);
    }

    file.flush();
    file.close();
    std::cout << "\nSimulación guardada en " << fs::absolute(ruta) << " (tmax=" << tmax << ", dt=" << dt << ")\n";
}
