#ifndef _ROC_GL_POINT_H_
#define _ROC_GL_POINT_H_

class Point2D
{
private:
    float m_XPos;
    float m_YPos;

public:
    Point2D(float x, float y)
        :m_XPos(x), m_YPos(y) {}
    
    float GetXStd() const { return m_XPos; }
    float GetYStd() const { return m_YPos; }
    float GetXGL(int screenX) const;
    float GetYGL(int screenY) const;

    void SetX(float x) { m_XPos = x; }
    void SetY(float y) { m_YPos = y; }
};

Point2D Lerp(Point2D& point1, Point2D point2, float t);

#endif