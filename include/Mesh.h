#ifndef MESH_H
#define MESH_H

// Classe de base pour le maillage
class IMesh {
public:
    virtual ~IMesh() = default;

    // Renvoie le nombre de points dans le maillage
    virtual int getNumberOfPoints() const = 0;

    // Renvoie la position d'un point donné (par indice)
    virtual double getPosition(int i) const = 0;

    // Alias pour la compatibilité avec le code existant
    int x_size() const { return getNumberOfPoints(); }
    double x_i(int i) const { return getPosition(i); }
};

// Maillage uniforme
class UniformMesh : public IMesh {
public:
    // Constructeur : initialise le maillage uniforme
    UniformMesh(double x_min, double x_max, double dx);

    // Implémentation des méthodes virtuelles
    int getNumberOfPoints() const override;
    double getPosition(int i) const override;

private:
    double x_min, x_max, dx; // Limites et pas du maillage
    int numPoints;           // Nombre de points dans le maillage
};

#endif
