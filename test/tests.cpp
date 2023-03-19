#include "gtest/gtest.h"

#include "../src/HeatMethod.h"
#include "../src/Marching.h"

TEST(GeodesicsTests, HeatMethodTests)
{
    // Read Mesh
    const char* filename = "../../meshes/hexagon_lvl1.off";
    Triangle_mesh mesh;
    ReadOFFMesh(mesh, filename);

    Vertex_index vertex1_idx(2);
    Vertex_index vertex2_idx(47);

    // check that distance for same vertex is zero
    double trivial_dist = ComputeGeodesicDistance(mesh, vertex1_idx, vertex1_idx);
    EXPECT_EQ(trivial_dist, 0.);

    // check for convergence under mesh refinement
    Point_3 vertex1 = mesh.point(vertex1_idx);
    Point_3 vertex2 = mesh.point(vertex2_idx);
    double eucli_dist = sqrt( CGAL::squared_distance(vertex1, vertex2) );

    double hm_dist = ComputeGeodesicDistance(mesh, vertex1_idx, vertex2_idx);

    EXPECT_EQ(hm_dist, eucli_dist);
}

TEST(GeodesicsTests, ShortestPathsTests)
{
    // Read Mesh
    const char* filename = "../../meshes/hexagon_lvl1.off";
    Triangle_mesh mesh;
    ReadOFFMesh(mesh, filename);

    Vertex_index vertex1_idx(2);
    Vertex_index vertex2_idx(47);

    // check that distance for same vertex is zero
    double trivial_dist = ComputeExactGeodesicDistance(mesh, vertex1_idx, vertex1_idx);
    EXPECT_EQ(trivial_dist, 0.);

    // check for exactness of geodesic
    Point_3 vertex1 = mesh.point(vertex1_idx);
    Point_3 vertex2 = mesh.point(vertex2_idx);
    double eucli_dist = sqrt( CGAL::squared_distance(vertex1, vertex2) );

    double sp_dist = ComputeExactGeodesicDistance(mesh, vertex1_idx, vertex2_idx);

    EXPECT_DOUBLE_EQ(sp_dist, eucli_dist);
}

TEST(GeodesicsTests, HeatMethodConvergence)
{
    // choose vertex locations
    Vertex_index vertex1(1);
    Vertex_index vertex2(4);

    // compute haet method distances
    std::vector<double> distances = DistancesUnderRefinementOfHexagonMesh(vertex1, vertex2);

    // Read Mesh
    const char* filename = "../../meshes/hexagon_lvl0.off";
    Triangle_mesh mesh;
    ReadOFFMesh(mesh, filename);

    double exact_distance = ComputeExactGeodesicDistance(mesh, vertex1, vertex2);

    // check for convergence
    if (distances[0] <= exact_distance)
    {
        for (int i = 1; i < distances.size(); ++i)
        {
            EXPECT_TRUE(distances[i-1] <= distances[i] <= exact_distance);
        }
    }
    else
    {
        for (int i = 1; i < distances.size(); ++i)
        {
            std::cout << distances[i-1] << " -> "
                      << distances[i] << " -> "
                      << exact_distance << std::endl;
            EXPECT_TRUE(distances[i-1] > distances[i] > exact_distance);
        }
    }

}


