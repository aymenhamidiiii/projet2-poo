#ifndef PROBLEM_H
#define PROBLEM_H

#include "Equation.h"
#include "Mesh.h"
#include "Variable.h"

class Problem {
public:
    // Constructeur
    Problem(IMesh* mesh, int max_iterations = 1000, double epsilon = 1e-5);
    
    // Destructeur
    ~Problem();

    // Vérification de la convergence
    bool has_converged(const Variable& u_k, const Variable& u_kp1, double epsilon = 1e-5);
    void solve_parallel();

    // Résolution du problème
    void solve();

private:
    IMesh* mesh;               // Pointeur vers le maillage
    Equation equation;         // Objet Equation pour les calculs
    int max_iterations;        // Nombre maximal d'itérations
    double epsilon;            // Critère de convergence
};

#endif // PROBLEM_H
