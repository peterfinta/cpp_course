#include "submission/shapes.h"
#include "submission/transformations.h"
#include "submission/operations.h"
#include "submission/voxel_grid.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "point3d.h"

Shape your_shape(); // implemented in your_shape.cpp

int main() {
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
    
    float piHalf = float(0.5*3.14159265358979323846);
    float pi = float(3.14159265358979323846);

    std::cout << "Cube{} " << Cube{}.getBounds() << std::endl; 
    std::cout << "Empty{} " << Empty{}.getBounds() << std::endl; 

    //std::cout << "Cube{} (" << Cube{}.getBounds().min.x << ", " << Cube{}.getBounds().min.y << ") "; 
    //std::cout << "(" << Cube{}.getBounds().max.x << ", " << Cube{}.getBounds().max.y << ") " << std::endl; 

    //std::cout << "Cube{}.translated(1.0f) (" << Cube{}.translated(1.0f).getBounds().min.x << ", " << Cube{}.translated(1.0f).getBounds().min.y << ") "; 
    //std::cout << "(" << Cube{}.translated(1.0f).getBounds().max.x << ", " << Cube{}.translated(1.0f).getBounds().max.y << ") " << std::endl; 

    //std::cout << "Cube{}.rotated(Axis::Z, piHalf) (" << Cube{}.rotated(Axis::Z, piHalf).getBounds().min.x << ", " << Cube{}.rotated(Axis::Z, piHalf).getBounds().min.y << ") "; 
    //std::cout << "(" << Cube{}.rotated(Axis::Z, piHalf).getBounds().max.x << ", " << Cube{}.rotated(Axis::Z, piHalf).getBounds().max.y << ") " << std::endl; 

    std::cout << "Cube{}.translated(1.0f).rotated(Axis::Z, piHalf) (" << Cube{}.translated(1.0f).rotated(Axis::Z, piHalf).getBounds().min.x << ", " << Cube{}.translated(1.0f).rotated(Axis::Z, piHalf).getBounds().min.y << ") "; 
    std::cout << "(" << Cube{}.translated(1.0f).rotated(Axis::Z, piHalf).getBounds().max.x << ", " << Cube{}.translated(1.0f).rotated(Axis::Z, piHalf).getBounds().max.y << ") " << std::endl; 
    // until implemented in task 6.4, this will throw an exception
    try {
        VoxelGrid vg = Empty{};//your_shape();
        std::cout << vg;
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
