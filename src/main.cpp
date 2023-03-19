#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "GeodesicAlgorithms.h"

int main()
{
    // Read Mesh
    const char* filename = "../../meshes/hexagon_lvl1.off";
    Triangle_mesh mesh;
    ReadOFFMesh(mesh, filename);

    // Set up Geodesics Computations
    Vertex_index vertex1(1);
    Point_3 v1 = mesh.point(vertex1);
    Vertex_index vertex2(4);
    Point_3 v2 = mesh.point(vertex2);
    std::cout << "Chosen vertices: " << vertex1 << " and " << vertex2 << std::endl
              << "with positions (" << v1.x() << ", " << v1.y() << ", " << v1.z()
              << ") and (" << v2.x() << ", " << v2.y() << ", " << v2.z() << ")" << std::endl;
    std::cout << "exact (euclidean) distance: " << sqrt(CGAL::squared_distance(v1, v2)) << std::endl << std::endl;

    // Shortest Paths
    double distanceSP = ComputeExactGeodesicDistance(mesh, vertex1, vertex2);
    std::cout << "Shortest path distance: " << distanceSP << std::endl;

    // Heat Method
    double distanceHM = ComputeGeodesicDistance(mesh, vertex1, vertex2);
    std::cout << "Heat method distance between vertices: " << distanceHM << std::endl;

    // investigate convergence on refined Hexagon meshes
    std::vector<double> distances = DistancesUnderRefinementOfHexagonMesh(vertex1, vertex2);
    std::cout << "Heat method distance over refinement levels (barycentric quadrisection):" << std::endl;
    for (double d : distances)
    {
        std::cout << d << std::endl;
    }

    return 0;
}
