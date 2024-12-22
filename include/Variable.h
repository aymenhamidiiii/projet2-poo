#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <string>
#include "Mesh.h"

class Variable {
public:
    // Constructeur
    Variable(const IMesh* mesh);

    // Opérateurs pour accéder aux valeurs
    double& operator[](int i);
    double operator[](int i) const;

    // Taille de la variable
    int size() const;

    // Gestion des noms de variables
    void set_name(const std::string& name);
    const std::string& get_name() const;

    // Méthode pour afficher et exporter les données
    void print(int iteration) const;

private:
    std::string m_name;  // Nom de la variable
    std::vector<double> values;  // Contient les valeurs de la variable
};

#endif
