/**
 * @file     Pendulo.cpp
 * @brief    implementacion de poo del pendulo
 * @author   Angie Gomez, Leonardo Tovar
 * @date     29/10/25
 * @version  1.0
 * @license  owner
 */
#include "Pendulo.h"

Pendulo::Pendulo(double theta0, double omega0, double g_, double l_, double m_)
    : theta(theta0), omega(omega0), g(g_), l(l_), m(m_) {}
