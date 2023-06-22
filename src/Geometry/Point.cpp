#include "Geometry/Point.hpp"

float Point2D::GetXGL(int screenX) const
{
    int screenXGL_int = screenX / 2;

    return (this->m_XPos - screenXGL_int) / screenXGL_int;
}

float Point2D::GetYGL(int screenY) const
{
    int screenYGL_int = screenY / 2;

    return (this->m_YPos - screenYGL_int) / screenYGL_int;
}

Point2D Lerp(Point2D& point1, Point2D point2, float t)
{
    float newX = point1.GetXStd() * (1 - t) + point2.GetXStd() * t;
    float newY = point1.GetYStd() * (1 - t) + point2.GetYStd() * t;
    return Point2D(newX, newY);
}