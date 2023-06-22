#ifndef _ROC_OVAL_GL_H_
#define _ROC_OVAL_GL_H_

#include <glad/gl.h>
#include "Geometry/Point.hpp"
#include "Roc_GL/Shader.hpp"
#include <vector>
#include <cmath>

#include "ECS/Roc_ECS.h"

#include "Interfaces/Object.hpp"

class Oval : 
public IStaticCreation<IObject, Oval, float, float, int, int>,
virtual public IObject
{
private:
    Entity me;

    GLuint m_VBA;
    GLuint m_VAO;
    std::vector<GLfloat> vertices;

    double angle = 0;

    //Point2D m_center;
    float m_height_from_center;
    float m_width_from_center;

    // Shader info
    // static GLuint fragshader;
    // static GLuint vertshader;
    static Shader* m_shader;

    static unsigned int remaining;

    void Frame_SetVertsCorrect();

protected:
    Oval();
    Oval(float width, float height, int centerX, int centerY);

public:
    
    ~Oval();

    float GetWidth() const { return m_width_from_center; }
    float GetHeight() const { return m_height_from_center; }
    float GetCenterX() const { Coordinator* cd = Coordinator::Get(); return cd->GetComponent<Transform>(me).x; }
    float GetCenterY() const { Coordinator* cd = Coordinator::Get(); return cd->GetComponent<Transform>(me).y; }
    double GetAngle() const { return angle; }

    void SetX(float x) { Coordinator* cd = Coordinator::Get(); cd->GetComponent<Transform>(me).x = x; }
    void SetY(float y) { Coordinator* cd = Coordinator::Get(); cd->GetComponent<Transform>(me).y = y; }
    void SetWidth(float width) { m_width_from_center = width; }
    void SetHeight(float height) { m_height_from_center = height; }
    void SetAngle(double angleDegrees) { angle = angleDegrees; }

    //IObject methods

    /** DO NOT USE OUTSIDE OF ISTATICCREATION */
    static Oval* CreateInternal(float width, float height, int centerX = 0, int centerY = 0);
    
    void Update(double deltatime) override;
    void Render() override;
};

#endif