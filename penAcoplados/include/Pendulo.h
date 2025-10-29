/**
 * @file     Pendulo.h
 * @brief    Encabezados de la clase pendulo
 * @author   Angie Gomez, Leonardo Tovar
 * @date     29/10/25
 * @version  1.0
 * @license  owner
 */
#ifndef PENDULO_H
#define PENDULO_H

#include <cmath>

class Pendulo {
public:
    double theta;      // ángulo
    double omega;      // velocidad angular
    double g;          // gravedad
    double l;          // longitud
    double m;          // MASA
    
    Pendulo(double theta0, double omega0, double g_ = 9.81, double l_ = 1.0, double m_ = 1.0);
}; // ¡CORREGIDO!

#endif
