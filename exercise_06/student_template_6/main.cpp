#include "submission/shapes.h"
#include "submission/transformations.h"
#include "submission/operations.h"
#include "submission/voxel_grid.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "point3d.h"

Shape your_shape(); // implemented in your_shape.cpp

int main(int argc, char *argv[]) {
    // My Test    
    /*
    Sphere sphere{};
    Cube cube{};
    And cubeAndSphere{cube, sphere};
    Or cubeOrSphere{cube, sphere};
    Not NotSphere{sphere};
    Cylinder cylinder{};

    Point3D point_1{};
    Point3D point_2{};

    point_1.x = 0.5f;
    point_2.x = 0.9f;
    point_2.y = 0.9f;

    std::cout << sphere.isInside(point_1) << ", " << sphere.isInside(point_2) << std::endl;
    std::cout << cube.isInside(point_1) << ", " << cube.isInside(point_2) << std::endl;
    std::cout << cylinder.isInside(point_1) << ", " << cylinder.isInside(point_2) << std::endl;
    std::cout << cubeAndSphere.isInside(point_1) << ", " << cubeAndSphere.isInside(point_2) << std::endl;
    std::cout << cubeOrSphere.isInside(point_1) << ", " << cubeOrSphere.isInside(point_2) << std::endl;
    std::cout << NotSphere.isInside(point_1) << ", " << NotSphere.isInside(point_2) << std::endl;
    */

    //std::cout << Cube{}.translated(1.0f).rotated(Axis::Z, float(0.5*3.14159265358979323846)).getBounds().min.x << std::endl;
    //std::cout << Cube{}.translated(1.0f).scaled(2.0f).rotated(Axis::Z, float(3.14159265358979323846)).getBounds().max.x << std::endl;

    /* ENTERPRISE NCC-1701 */
    float pi = float(3.14159265358979323846);
    //Shape viewBox = Cube{}.scaled(Point3D{2.0f, 1.2f, 2.0f}) - Cube{}.scaled(Point3D{2.0f, 2.0f, 2.0f});
    //Shape saucer1 = Cylinder{}.scaled(Point3D{1.0f, 1.0f, 0.1f}).translated(Point3D{0.0f, 1.0f, 0.0f});
    //Shape saucer2 = Sphere{}.scaled(Point3D{0.3f, 0.3f, 0.2f}).translated(Point3D{0.0f, 1.0f, 0.0f});
    //Shape hull    = Cylinder{}.scaled(Point3D{0.3f, 0.3f, 0.8f}).rotated(Axis::X, 0.5f * pi).translated(Point3D{0.0f, -0.8f, -1.0f});
    //Shape neck    = 
    //Shape ship    = viewBox + saucer1 + saucer2 + hull;
    //std::cout << ship;
    
    float fraction;
    sscanf(argv[1], "%f", &fraction);
    std::cout << Cube{}.scaled(Point3D{2.0f, 1.0f, 1.0f}).rotated(Axis::Z, fraction * pi);

    try {
        //VoxelGrid vg = your_shape();
        //std::cout << vg;
        //Sphere sphere{};
        //Cube cube{};
        //Octahedron octa{};
        //Not notSphere(sphere);
        //And cubeAndNotSphere{cube, notSphere};
        //Or cubeOrSphere{cube, sphere};
        //Shape newShape = sphere.scaled(Point3D{2.0f});
        //std::cout << VoxelGrid(cube.rotated(Axis::Z, 1.5f));
    }
    catch (std::logic_error& e) {
        std::cout << "you need to implement " << e.what() << " to get some output here!" << std::endl;
    }

    return EXIT_SUCCESS;
}
