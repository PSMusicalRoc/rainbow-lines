#ifndef _ROC_SPLINE_GL_H_
#define _ROC_SPLINE_GL_H_

#include "Geometry/Point.hpp"

class Spline
{
private:
    Point2D point0, point1, point2, point3;

public:
    Spline(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3)
        :point0(p0), point1(p1), point2(p2), point3(p3) {}
    
    // Render() function tbd

    Point2D LerpCubic(float t);
};

#endif