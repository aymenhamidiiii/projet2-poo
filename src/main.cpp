#include "Problem.h"
#include "Mesh.h"
#include <iostream>
#include <memory> // Pour std::unique_ptr

int main() {
    // Maillage 
    std::unique_ptr<IMesh> mesh = std::make_unique<UniformMesh>(0.0, 1.0, 0.01); // dx = 0.01 pour plus de calculs

    // Crée un problème et teste les deux modes
    Problem problem(mesh.get());

    std::cout << "=== Mode Séquentiel ===" << std::endl;
    problem.solve();

    std::cout << "\n=== Mode Parallèle ===" << std::endl;
    problem.solve_parallel();

    return 0;
}
