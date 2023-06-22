#include "Geometry/Spline.hpp"

Point2D Spline::LerpCubic(float t)
{
    // First set
    Point2D l1 = Lerp(point0, point1, t);
    Point2D l2 = Lerp(point1, point2, t);
    Point2D l3 = Lerp(point2, point3, t);

    // Second Set
    Point2D l4 = Lerp(l1, l2, t);
    Point2D l5 = Lerp(l2, l3, t);

    // Final
    return Lerp(l4, l5, t);
}