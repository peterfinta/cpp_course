#pragma once

#include "shapes.h"

#include <memory>

/// shared abstract transformation base class containing a nested shape to be transformed
class Transformation : public Shape {
protected:
    Transformation(const Shape& shape);
public:
    Shape sub_shape;
};

// of course, one could implement all these transformations jointly as a single transformation matrix.
// for simplicity, we don't do that here.

class Scaled final : public Transformation {
public:
    Scaled(const Shape& shape, const Point3D& s) 
      : Transformation(shape) {scale = s;};
    Point3D scale;
private:
    AABB getBounds_impl() const override;
    Shape clone_impl() const override;
    bool isInside_impl(const Point3D& p) const override;
};

class Translated final : public Transformation {
public:
    Translated(const Shape& shape, const Point3D& t) 
      : Transformation(shape) {offset = t;};
    Point3D offset;
private:
    AABB getBounds_impl() const override;
    Shape clone_impl() const override;
    bool isInside_impl(const Point3D& p) const override;
};

class Rotated final : public Transformation {
public:
    Rotated(const Shape& shape, const float& a) 
      : Transformation(shape) {angle = a;};
    float angle;
private:
    AABB getBounds_impl() const override;
    Shape clone_impl() const override;
    bool isInside_impl(const Point3D& p) const override;
};
