#include "GeodesicAlgorithms.h"

void
ReadOFFMesh(
        Triangle_mesh& mesh,
        const char* filename)
{
    std::ifstream input_file(filename);

    if( !CGAL::read_off(input_file, mesh) )
    {
        std::cerr << "Failed to read input mesh (probably either not found or non-manifold): " << filename << std::endl;
        EXIT_FAILURE;
    }
}

void
WriteOFFMesh(
        Triangle_mesh& mesh,
        const char* filename)
{
    std::ofstream output_file(filename);

    if ( !CGAL::write_off(output_file, mesh) )
    {
        std::cerr << "Mesh can not be written to .off file." << std::endl;
        EXIT_FAILURE;
    }
}

double
ComputeExactGeodesicDistance(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2)
{
    auto source_vertex = vertices(mesh).begin() + vertex1;
    auto target_vertex = vertices(mesh).begin() + vertex2;

    Surface_mesh_shortest_path shortest_path(mesh);
    shortest_path.add_source_point(*source_vertex);
    double distance = shortest_path.shortest_distance_to_source_points(*target_vertex).first;

    return distance;
}

double
ComputeGeodesicDistance(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2)
{
    assert(0 <= vertex1 < mesh.num_vertices());
    assert(0 <= vertex2 < mesh.num_vertices());

    auto source_vertex = vertices(mesh).begin() + vertex1;
    auto target_vertex = vertices(mesh).begin() + vertex2;

    Vertex_distance_map vertex_distance = mesh.add_property_map<vertex_descriptor,double>("v:distance",0).first;

    CGAL::Heat_method_3::estimate_geodesic_distances(mesh, vertex_distance, *source_vertex);

    double distance = vertex_distance[*target_vertex];
    return distance;
}

std::vector<double>
DistancesUnderRefinement(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2,
        int refinement_levels,
        bool output_meshes)
{
    std::vector<double> distances;
    distances.resize(refinement_levels+1);

    distances[0] = ComputeGeodesicDistance(mesh, vertex1, vertex2);

    for (int i=0; i<refinement_levels; ++i)
    {
        // crate Polyhedron_3 from Surface_mesh
        Polyhedron_3 poly_mesh;
        CGAL::copy_face_graph(mesh, poly_mesh);

        // refine poly mesh
        std::vector<Facet_handle> new_facets;
        std::vector<Vertex_handle> new_vertices;
        CGAL::Polygon_mesh_processing::refine(poly_mesh, faces(poly_mesh),
                                              std::back_inserter(new_facets),
                                              std::back_inserter(new_vertices),
                                              CGAL::parameters::density_control_factor(1.75));
        std::cout << poly_mesh.size_of_vertices() << std::endl;

        // get Surface_mesh
        CGAL::copy_face_graph(poly_mesh, mesh);

        if ( output_meshes ) {
            // write mesh to file
            std::string filename = "../mesh_lvl" + std::to_string(i+1) + ".off";
            WriteOFFMesh(mesh, filename.c_str());
        }

        // compute new geodesic
        distances[i+1] = ComputeGeodesicDistance(
                    mesh, vertex1, vertex2);
    }

    return distances;
}

std::vector<double>
DistancesUnderRefinementOfHexagonMesh(
        Vertex_index vertex1,
        Vertex_index vertex2)
{
    int max_level = 6;
    std::vector<double> distances(max_level);//+1);

    for (int l = 0; l < max_level; ++l)
    {
        std::string filename = "../../meshes/hexagon_lvl" + std::to_string(l+1) + ".off";
        Triangle_mesh mesh;
        ReadOFFMesh(mesh, filename.c_str());
        distances[l] = ComputeGeodesicDistance(mesh, vertex1, vertex2);
    }
    return distances;
}
