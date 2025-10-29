/**
 * @file     SistemaAcoplado.h
 * @brief    Encabezados de la clase SistemaAcoplado
 * @author   Angie Gomez, Leonardo Tovar
 * @date     29/10/25
 * @version  1.0
 * @license  owner
 */
#ifndef SISTEMA_ACOPLADO_H
#define SISTEMA_ACOPLADO_H

#include "Pendulo.h"
#include <string>

class SistemaAcoplado {
public:
    Pendulo p1, p2;
    double kappa;

    SistemaAcoplado(Pendulo p1_, Pendulo p2_, double kappa_);

    // Método principal de simulación
    void simular(double tmax, double dt, const std::string& filename);

    // Método para calcular un paso de tiempo (Runge-Kutta 4)
    void paso_rk4(double dt);

    // ===================================
    // NUEVOS MÉTODOS PARA CÁLCULO DE ENERGÍA
    // ===================================

    // Calcula la Energía Cinética de un péndulo
    double ke(const Pendulo& p) const;
    
    // Calcula la Energía Potencial Gravitacional de un péndulo
    double pe_grav(const Pendulo& p) const;
    
    // Calcula la Energía Potencial de Acoplamiento (del sistema)
    double pe_acople() const;

    // Calcula la Energía Total del Sistema Acoplado
    double energia_total() const;
    
    // Método auxiliar (aunque no se usa directamente en el main, es necesario si se implementó)
    double energia_pendulo(const Pendulo& p, const Pendulo& otro) const;


private:
};
#endif
