#include "transformations.h"
#include <cmath>

// helper function for 2D rotations
std::pair<float, float> rotate2D(float x, float y, float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return {cos*x-sin*y, sin*x+cos*y};
}

Point3D rotate(const Point3D& p, Axis axis, float angle) {
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);
    switch(axis) {
        case Axis::X:
            return Point3D{p.x, cos*p.y - sin*p.z, sin*p.y + cos*p.z};
        case Axis::Y:
            return Point3D{sin*p.z + cos*p.x, p.y, cos*p.z - sin*p.x};
        case Axis::Z:
            return Point3D{cos*p.x - sin*p.y, sin*p.x + cos*p.y, p.z};
    }
}


Transformation::Transformation(const Shape& shape)
    : sub_shape{shape.clone()}
{

}

Shape Scaled::clone_impl() const {
    return {std::make_shared<Scaled>(sub_shape, scale)};
}

bool Scaled::isInside_impl(const Point3D& p) const {
    return sub_shape.isInside(p / scale); 
}

AABB Scaled::getBounds_impl() const {
    return AABB{(sub_shape.getBounds().min) * scale,
                (sub_shape.getBounds().max) * scale};
}

Shape Translated::clone_impl() const {
    return {std::make_shared<Translated>(sub_shape, offset)};
}

bool Translated::isInside_impl(const Point3D& p) const {
    return sub_shape.isInside(p - offset); 
}

AABB Translated::getBounds_impl() const {
    return AABB{sub_shape.getBounds().min + offset,
                sub_shape.getBounds().max + offset};
}

Shape Rotated::clone_impl() const {
    return {std::make_shared<Rotated>(sub_shape, axis, angle)};
}

// TODO: Rotated is fucked up as hell, one needs to get the aabb from the 
// sub_shape and fix this trainwreck!
bool Rotated::isInside_impl(const Point3D& p) const {
    return sub_shape.isInside(rotate(p, axis, -1.0f * angle));
}

AABB Rotated::getBounds_impl() const {
    Point3D boundsOffset = (sub_shape.getBounds().min 
                          + sub_shape.getBounds().max) * Point3D(0.5f);
    const float sin = std::abs(std::sin(angle));
    const float cos = std::abs(std::cos(angle));
    Point3D oldMin = sub_shape.getBounds().min - boundsOffset;
    Point3D oldMax = sub_shape.getBounds().max - boundsOffset;
    Point3D newMin = sub_shape.getBounds().min - boundsOffset;
    Point3D newMax = sub_shape.getBounds().max - boundsOffset;
    switch(axis) {
        case Axis::X:
            newMin.y = cos*oldMin.y + sin*oldMin.z;
            newMin.z = cos*oldMin.z + sin*oldMin.y;
            newMax.y = cos*oldMax.y + sin*oldMax.z;
            newMax.z = cos*oldMax.z + sin*oldMax.y;
            break;
        case Axis::Y:
            newMin.z = cos*oldMin.z + sin*oldMin.x;
            newMin.x = cos*oldMin.x + sin*oldMin.z;
            newMax.z = cos*oldMax.z + sin*oldMax.x;
            newMax.x = cos*oldMax.x + sin*oldMax.z;
            break;
        case Axis::Z:
            newMin.x = cos*oldMin.x + sin*oldMin.y;
            newMin.y = cos*oldMin.y + sin*oldMin.x;
            newMax.x = cos*oldMax.x + sin*oldMax.y;
            newMax.y = cos*oldMax.y + sin*oldMax.x;
            break;
    }
    return AABB{newMin + rotate(boundsOffset, axis, angle), 
                newMax + rotate(boundsOffset, axis, angle)};
}
