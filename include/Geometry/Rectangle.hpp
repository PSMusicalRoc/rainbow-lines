#ifndef _ROC_RECTANGLE_GL_HPP_
#define _ROC_RECTANGLE_GL_HPP_

#include "Geometry/Point.hpp"
#include "Interfaces/Object.hpp"
#include "Roc_GL/Shader.hpp"
#include <glad/gl.h>

class Rectangle :
public IStaticCreation<IObject, Rectangle>,
virtual public IObject
{
private:
    static Shader* m_shader;
    static unsigned int remaining;

    GLuint m_VAO;
    GLuint m_VBA;

    std::vector<GLfloat> vertices;

protected:
    Rectangle();
    ~Rectangle();

public:
    /** DO NOT USE OUTSIDE OF ISTATICCREATION */
    static Rectangle* CreateInternal() { return new Rectangle(); }
    void Render() override;
};


#endif