#pragma once

#include <iterator>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh/IO.h>

#include <CGAL/Heat_method_3/Surface_mesh_geodesic_distances_3.h>
#include <CGAL/Surface_mesh_shortest_path.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/copy_face_graph.h>
#include <CGAL/Polygon_mesh_processing/refine.h>

typedef CGAL::Simple_cartesian<double>              Kernel;
typedef Kernel::Point_3                             Point_3;
typedef CGAL::Surface_mesh<Point_3>                 Triangle_mesh;
typedef CGAL::Surface_mesh<Point_3>::Vertex_index   Vertex_index;

typedef boost::graph_traits<Triangle_mesh>::vertex_descriptor   vertex_descriptor;
typedef boost::graph_traits<Triangle_mesh>::face_descriptor     face_descriptor;

typedef Triangle_mesh::Property_map<vertex_descriptor,double>   Vertex_distance_map;
typedef CGAL::Surface_mesh_shortest_path_traits<Kernel, Triangle_mesh>  Traits;
typedef CGAL::Surface_mesh_shortest_path<Traits>                Surface_mesh_shortest_path;

typedef CGAL::Polyhedron_3<Kernel>      Polyhedron_3;
typedef Polyhedron_3::Facet_handle      Facet_handle;
typedef Polyhedron_3::Vertex_handle     Vertex_handle;

void
ReadOFFMesh(
        Triangle_mesh& mesh,
        const char* filename);

double
ComputeExactGeodesicDistance(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2);

double
ComputeGeodesicDistance(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2);

std::vector<double>
DistancesUnderRefinement(
        Triangle_mesh& mesh,
        Vertex_index vertex1,
        Vertex_index vertex2,
        int refinement_levels,
        bool output_meshes = false);

std::vector<double>
DistancesUnderRefinementOfHexagonMesh(
        Vertex_index vertex1,
        Vertex_index vertex2);
