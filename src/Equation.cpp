#include "Variable.h"
#include "Equation.h"
#include <iostream>

void Equation::compute(Variable& u_k, Variable& u_kp1, IMesh* mesh) {
    int nPoints = mesh->getNumberOfPoints();
    for (int i = 1; i < nPoints - 1; ++i) {
        u_kp1[i] = 0.5 * (u_k[i - 1] + u_k[i + 1]);
    }
}

void Equation::compute_initial_condition(Variable& u, IMesh* mesh, double T1, double T2) {
    int nPoints = mesh->getNumberOfPoints();
    for (int i = 0; i < nPoints; ++i) {
        double x = mesh->getPosition(i);
        if (x < 0.5) {
            u[i] = T1; // Condition initiale pour T1
        } else {
            u[i] = T2; // Condition initiale pour T2
        }
    }
}

void Equation::compute_boundary_conditions(Variable& u, double T1, double T2) {
    u[0] = T1;  // Condition aux bords (gauche)
    u[u.size() - 1] = T2;  // Condition aux bords (droit)
}

void Equation::compute_exact_solution(Variable& u_ref, IMesh* mesh, double T1, double T2) {
    int numPoints = mesh->getNumberOfPoints();
    for (int i = 0; i < numPoints; ++i) {
        double x = mesh->getPosition(i);
        u_ref[i] = T1 * (1 - x) + T2 * x; // Solution exacte : interpolation linéaire
    }
}
