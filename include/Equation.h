#ifndef EQUATION_H
#define EQUATION_H

#include "Variable.h"
#include "Mesh.h"

class Equation {
public:
    void compute(Variable& u_k, Variable& u_kp1, IMesh* mesh);
    void compute_initial_condition(Variable& u, IMesh* mesh, double T1, double T2); // Ajout de T1 et T2
    void compute_boundary_conditions(Variable& u, double T1, double T2); // Ajout de T1 et T2
    void compute_exact_solution(Variable& u_ref, IMesh* mesh, double T1, double T2);
};

#endif
