#include "Variable.h"
#include <fstream>
#include <iostream>

// Constructeur
Variable::Variable(const IMesh* mesh) {
    values.resize(mesh->getNumberOfPoints(), 0.0);  // Utilisation de getNumberOfPoints
}

// Accès aux valeurs via l'opérateur []
double& Variable::operator[](int i) {
    return values[i];
}

double Variable::operator[](int i) const {
    return values[i];
}

// Obtenir la taille
int Variable::size() const {
    return values.size();
}

// Définir le nom de la variable
void Variable::set_name(const std::string& name) {
    m_name = name;
}

// Obtenir le nom de la variable
const std::string& Variable::get_name() const {
    return m_name;
}

//Affichage et export

// Affichage et export
void Variable::print(int iteration) const {
    // Affichage dans la console
    std::cout << "Variable: " << m_name << ", Iteration: " << iteration << "\n";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i] << " ";
    }
    std::cout << "\n";

    // Exporter les données dans un fichier spécifique à l'itération
    // Ouvrir le fichier en mode append pour ne pas écraser les valeurs précédentes
    std::ofstream file("Variable_" + m_name + ".data", std::ios::app);
    for (size_t i = 0; i < values.size(); ++i) {
        file << iteration << " " << values[i] << "\n";  // Enregistrer l'itération et la valeur
    }
    file.close();
}


