#ifndef _ROC_TRIANGLE_GL_H_
#define _ROC_TRIANGLE_GL_H_

#include "Classes/Interfaces/Renderable.hpp"
#include <glad/gl.h>

class Triangle : virtual public IRenderable
{
private:
    GLuint m_VBA;
    GLuint m_VAO;
    std::vector<GLfloat> vertices;

    static GLuint fragshader;
    static GLuint vertshader;
    static GLuint program;

public:
    Triangle();
    ~Triangle()
    {
        glDeleteBuffers(1, &m_VBA);
        m_VBA = 0;
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;

        if (program)
        {
            glDeleteProgram(program);
            program = 0;
        }
    }

    void Render() override;

};

#endif