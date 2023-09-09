#include "transformations.h"
#include <cmath>

// helper function for 2D rotations
std::pair<float, float> rotate2D(float x, float y, float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return {cos*x-sin*y, sin*x+cos*y};
}


Transformation::Transformation(const Shape& shape)
    : sub_shape{shape.clone()}
{

}

Shape Scaled::clone_impl() const {
    return {std::make_shared<Scaled>(sub_shape, scale)};
}

bool Scaled::isInside_impl(const Point3D& p) const {
    return isInside(p / scale); 
}

AABB Scaled::getBounds_impl() const {
    return AABB{Point3D{-1.0f} * scale, Point3D{1.0f} * scale};
}

Shape Translated::clone_impl() const {
    return {std::make_shared<Translated>(sub_shape, offset)};
}

bool Translated::isInside_impl(const Point3D& p) const {
    return isInside(p - offset); 
}

AABB Translated::getBounds_impl() const {
    return AABB{Point3D{-1.0f} - offset, Point3D{1.0f} - offset};
}

Shape Rotated::clone_impl() const {
    return {std::make_shared<Rotated>(sub_shape, angle)};
}

bool Rotated::isInside_impl(const Point3D& p) const {
    std::pair<float, float> rotatedXY = rotate2D(p.x, p.y, -1.0f * angle);
    return isInside(Point3D{rotatedXY.first, rotatedXY.second, p.z}); 
}

AABB Rotated::getBounds_impl() const {
    std::pair<float, float> rotatedXY = rotate2D(1.0f, 1.0f, -1.0f * angle);
    return AABB{Point3D{-1.0f*rotatedXY.first, -1.0f*rotatedXY.second, -1.0f},
                Point3D{rotatedXY.first, rotatedXY.second, 1.0f}};
}
