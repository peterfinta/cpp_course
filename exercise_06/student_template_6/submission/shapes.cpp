#include "shapes.h"

#include "transformations.h"
#include "operations.h"
#include "point3d.h"

#include <stdexcept>

Shape::Shape(std::shared_ptr<Shape>&& shape) noexcept
    : instance{std::move(shape)} // take ownership
{

}

Shape Shape::clone() const
{
    // if this shape just contains a pointer, we can return a simple copy
    if (instance)
        return *this;

    // otherwise, call the derived clone implementation
    return clone_impl();
}

AABB Shape::getBounds() const {
    // call the nested shape (if any)
    if (instance)
        return instance->getBounds();

    // otherwise, call the derived getBounds implementation
    return getBounds_impl();
}

bool Shape::isInside(const Point3D& p) const
{
    // call the nested shape (if any)
    if (instance)
        return instance->isInside(p);

    // otherwise, call the derived isInside implementation
    return isInside_impl(p);
}

Shape Shape::clone_impl() const
{
    // no default implementation available (but cannot set = 0, since we want to have instances of Shape)
    // if you get this error, you forgot to implement the override
    throw std::logic_error("clone called on an abstract shape");
}

AABB Shape::getBounds_impl() const
{
    // fallback default implementation
    return AABB{-1.0f, 1.0f};
}

bool Shape::isInside_impl(const Point3D&) const
{
    // no fallback implementation (but cannot set = 0, since we want to have instances of Shape)
    // if you get this error, you forgot to implement the override
    throw std::logic_error("isInside called on an abstract shape");
}

Shape Empty::clone_impl() const
{
    return {std::make_shared<Empty>()};
}

bool Empty::isInside_impl(const Point3D&) const {
    return false;
}

AABB Empty::getBounds_impl() const
{
    return AABB{};
}

Shape Cube::clone_impl() const
{
    return {std::make_shared<Cube>()};
}

bool Cube::isInside_impl(const Point3D& p) const {
    return getBounds().contains(p);
}

Shape Sphere::clone_impl() const {
    return {std::make_shared<Sphere>()};
}

bool Sphere::isInside_impl(const Point3D& p) const {
    Point3D zero{};
    return (1 >= distance(p, zero));
}

Shape Cylinder::clone_impl() const {
    return {std::make_shared<Cylinder>()};
}

bool Cylinder::isInside_impl(const Point3D& p) const {
    Point3D zeroPlane(0.0f, 0.0f, p.z);
    return (p.z >= -1.0f && p.z <= 1.0f) && distance(p, zeroPlane);
}
