#ifndef _ROC_OVAL_GL_H_
#define _ROC_OVAL_GL_H_

#include <glad/gl.h>
#include "Classes/Point.hpp"
#include "Roc_GL/Shader.hpp"
#include <vector>
#include <cmath>

#include "Classes/Interfaces/Renderable.hpp"

class Oval : virtual public IRenderable
{
private:
    GLuint m_VBA;
    GLuint m_VAO;
    std::vector<GLfloat> vertices;

    GLuint angle = 0;

    Point2D m_center;
    float m_height_from_center;
    float m_width_from_center;

    // Shader info
    // static GLuint fragshader;
    // static GLuint vertshader;
    static GLuint program;

    static unsigned int remaining;

public:
    Oval();
    Oval(float width, float height, int centerX = 0, int centerY = 0);
    ~Oval();
    
    void Frame_SetVertsCorrect(int screenX, int screenY);

    float GetWidth() const { return m_width_from_center; }
    float GetHeight() const { return m_height_from_center; }
    float GetCenterX() const { return m_center.GetXStd(); }
    float GetCenterY() const { return m_center.GetYStd(); }
    float GetAngle() const { return angle; }

    void SetX(float x) { m_center.SetX(x); }
    void SetY(float y) { m_center.SetY(y); }
    void SetWidth(float width) { m_width_from_center = width; }
    void SetHeight(float height) { m_height_from_center = height; }
    void SetAngle(float angleDegrees) { angle = angleDegrees; }

    void Render() override;
};

#endif