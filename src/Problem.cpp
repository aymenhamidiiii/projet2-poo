#include "Problem.h"
#include "Variable.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Timer.h"
#include <thread>
#include <mutex>

// Constructeur et destructeur
Problem::Problem(IMesh* mesh, int max_iterations, double epsilon)
    : mesh(mesh), max_iterations(max_iterations), epsilon(epsilon) {}

Problem::~Problem() {
    delete mesh;
}

bool Problem::has_converged(const Variable& u_k, const Variable& u_kp1, double epsilon) {
    double max_diff = 0.0;

    for (int i = 0; i < u_k.size(); ++i) {
        double diff = std::abs(u_kp1[i] - u_k[i]);
        max_diff = std::max(max_diff, diff);
    }

    return max_diff < epsilon;
}

// Méthode séquentielle
void Problem::solve() {
    std::cout << "--- Début de la résolution séquentielle ---" << std::endl;

    Variable u_k(mesh), u_kp1(mesh), u_ref(mesh);
    Equation equation;

    double T1 = 30.0; // Température au bord gauche
    double T2 = 15.0; // Température au bord droit

    // Initialisation des fichiers de sauvegarde
    std::ofstream file_initial("output/initial_condition.dat");
    std::ofstream file_exact("output/exact_solution.dat");
    std::ofstream file_jacobi("output/jacobi_solution.dat");

    // Vérification de l'ouverture des fichiers
    if (!file_initial || !file_exact || !file_jacobi) {
        std::cerr << "Erreur : Impossible d'ouvrir les fichiers pour l'écriture des résultats !" << std::endl;
        return;
    }

    file_initial << "# x u_initial\n";
    file_exact << "# x u_exact\n";
    file_jacobi << "# x u_jacobi\n";

    // Calcul de la solution exacte
    equation.compute_exact_solution(u_ref, mesh, T1, T2);

    // Initialisation de la condition initiale
    equation.compute_initial_condition(u_k, mesh, T1, T2);

    // Sauvegarde de la condition initiale
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_initial << mesh->x_i(i) << " " << u_k[i] << "\n";
    }

    // Sauvegarde de la solution exacte
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_exact << mesh->x_i(i) << " " << u_ref[i] << "\n";
    }

    Timer total_timer, iteration_timer;
    total_timer.start();

    int iteration = 0;

    // Résolution par méthode itérative
    while (iteration < max_iterations) {
        iteration_timer.start();
        ++iteration;

        equation.compute_boundary_conditions(u_kp1, T1, T2);
        equation.compute(u_k, u_kp1, mesh);

        iteration_timer.stop();
        iteration_timer.print("Temps pour l'itération " + std::to_string(iteration));

        if (has_converged(u_k, u_kp1)) {
            std::cout << "Convergence atteinte après " << iteration << " itérations." << std::endl;
            break;
        }

        for (int i = 0; i < mesh->x_size(); ++i) {
            u_k[i] = u_kp1[i];
        }
    }

    total_timer.stop();
    total_timer.print("Temps total du calcul séquentiel");

    if (iteration == max_iterations) {
        std::cout << "Nombre maximum d'itérations atteint sans convergence." << std::endl;
    }

    // Sauvegarde de la solution finale (Jacobi)
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_jacobi << mesh->x_i(i) << " " << u_kp1[i] << "\n";
    }

    file_initial.close();
    file_exact.close();
    file_jacobi.close();

    std::cout << "--- Fin de la résolution séquentielle ---" << std::endl;

    // Génération du script Gnuplot
    std::ofstream gnuplot_script("output/plot.gnuplot");
    gnuplot_script << "set terminal png size 800,600\n";
    gnuplot_script << "set output 'output/solutions.png'\n";
    gnuplot_script << "set xlabel 'Position (x)'\n";
    gnuplot_script << "set ylabel 'Temperature (T)'\n";
    gnuplot_script << "set title 'Profil de température'\n";
    gnuplot_script << "set key top right\n";
    gnuplot_script << "plot 'output/initial_condition.dat' using 1:2 with lines title 'Condition Initiale' lw 2 lc rgb 'cyan', \\\n";
    gnuplot_script << "     'output/exact_solution.dat' using 1:2 with lines title 'Solution Exacte' lw 2 lc rgb 'green', \\\n";
    gnuplot_script << "     'output/jacobi_solution.dat' using 1:2 with lines title 'Solution Jacobi' lw 2 lc rgb 'purple'\n";
    gnuplot_script.close();

    // Exécution de Gnuplot
    std::cout << "Exécution de Gnuplot pour générer le graphique..." << std::endl;
    system("gnuplot output/plot.gnuplot");
    std::cout << "Graphique généré : output/solutions.png" << std::endl;
}


// Méthode parallèle
void Problem::solve_parallel() {
    std::cout << "--- Début de la résolution parallèle ---" << std::endl;

    Variable u_k_jacobi(mesh), u_kp1_jacobi(mesh);
    Variable u_k_gs(mesh), u_kp1_gs(mesh);
    Equation equation;

    double T1 = 30.0;
    double T2 = 15.0;

    Timer total_timer;
    total_timer.start();

    int max_iterations_parallel = 100; // Pour rendre la différence visible
    std::mutex mtx;

    // Thread pour Jacobi
    std::thread jacobi_thread([&]() {
        for (int iteration = 0; iteration < max_iterations_parallel; ++iteration) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                equation.compute_boundary_conditions(u_kp1_jacobi, T1, T2);
            }
            equation.compute(u_k_jacobi, u_kp1_jacobi, mesh);
            for (int i = 0; i < mesh->x_size(); ++i) {
                u_k_jacobi[i] = u_kp1_jacobi[i];
            }
        }
        std::cout << "Jacobi terminé après " << max_iterations_parallel << " itérations." << std::endl;
    });

    // Thread pour Gauss-Seidel
    std::thread gauss_seidel_thread([&]() {
        for (int iteration = 0; iteration < max_iterations_parallel; ++iteration) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                equation.compute_boundary_conditions(u_kp1_gs, T1, T2);
            }
            equation.compute(u_k_gs, u_kp1_gs, mesh);
            for (int i = 0; i < mesh->x_size(); ++i) {
                u_k_gs[i] = u_kp1_gs[i];
            }
        }
        std::cout << "Gauss-Seidel terminé après " << max_iterations_parallel << " itérations." << std::endl;
    });

    // Attendre la fin des threads
    jacobi_thread.join();
    gauss_seidel_thread.join();

    total_timer.stop();
    total_timer.print("Temps total en parallèle");

    std::cout << "--- Fin de la résolution parallèle ---" << std::endl;
}
