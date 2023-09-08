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
    Sphere sphere{};
    Cube cube{};
    Point3D point_1{};
    Point3D point_2{};

    point_1.x = 0.5f;
    point_2.x = 0.9f;
    point_2.y = 0.9f;

    std::cout << sphere.isInside(point_1) << ", " << sphere.isInside(point_2) << std::endl;
    std::cout << cube.isInside(point_1) << ", " << cube.isInside(point_2) << std::endl;


    // until implemented in task 6.4, this will throw an exception
    try {
        VoxelGrid vg = your_shape();
        std::cout << vg;
    }
    catch (std::logic_error& e) {
        std::cout << "you need to implement " << e.what() << " to get some output here!" << std::endl;
    }

    return EXIT_SUCCESS;
}
