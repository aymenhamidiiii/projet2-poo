#include "Mesh.h"
#include <cmath> // Pour std::ceil

UniformMesh::UniformMesh(double x_min, double x_max, double dx)
    : x_min(x_min), x_max(x_max), dx(dx) {
    numPoints = static_cast<int>(std::ceil((x_max - x_min) / dx)) + 1;
}

int UniformMesh::getNumberOfPoints() const {
    return numPoints;
}

double UniformMesh::getPosition(int i) const {
    return x_min + i * dx;
}
