#include "operations.h"

Operation::Operation(const Shape& shape_a, const Shape& shape_b)
    : sub_shape_a{shape_a.clone()}, sub_shape_b{shape_b.clone()}
{

}

AABB Operation::getBounds_impl() const
{
    return sub_shape_a.getBounds()+sub_shape_b.getBounds();
}

And::And(const Shape& shape_a, const Shape& shape_b) : Operation(shape_a, shape_b){}

Shape And::clone_impl(const Shape& shape_a, const Shape& shape_b) const {
    return {std::make_shared<And>(shape_a, shape_b)};
}
//
//bool And::isInside_impl(const Point3D& p) const {
//    return sub_shape_a.isInside(p) 
//        && sub_shape_b.isInside(p);
//}
//
//Shape Or::clone_impl() const {
//    return {std::make_shared<Or>()};
//}
//
//bool Or::isInside_impl(const Point3D& p) const {
//    return sub_shape_a.isInside(p) 
//        || sub_shape_b.isInside(p);
//}
//
//Shape Xor::clone_impl() const {
//    return {std::make_shared<Xor>()};
//}
//
//bool Xor::isInside_impl(const Point3D& p) const {
//    return !sub_shape_a.isInside(p) 
//        != !sub_shape_b.isInside(p);
//}

//Not::Not(const Shape& shape_a) : Operation(shape_a, shape_a){};
//
//Shape Not::clone_impl() const {
//    return {std::make_shared<Not>()};
//}
//
//bool Not::isInside_impl(const Point3D& p) const {
//    return !sub_shape_a.isInside(p);
//}
