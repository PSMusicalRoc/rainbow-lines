#include "Geometry/Rectangle.hpp"

Shader* Rectangle::m_shader = nullptr;
unsigned int Rectangle::remaining = 0;

Rectangle::Rectangle()
:IObject()
{
    vertices = {
        -1.0f,  1.0f, 0.2f,
         1.0f,  1.0f, 0.2f,
         1.0f, -1.0f, 0.2f,
        -1.0f, -1.0f, 0.2f
    };

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBA);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Position vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (!m_shader)
    {
        m_shader = new Shader("shaders/Rectangle/vertex_shader.glsl", "shaders/Rectangle/fragment_shader.glsl");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    remaining++;
}

Rectangle::~Rectangle()
{
    glDeleteBuffers(1, &m_VBA);
    glDeleteVertexArrays(1, &m_VAO);
    remaining--;
    if (m_shader && !remaining)
    {
        m_shader->DeleteShader();
        m_shader = nullptr;
    }
}

void Rectangle::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBA);    
    glBindVertexArray(m_VAO);
    
    m_shader->Use();

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);
}