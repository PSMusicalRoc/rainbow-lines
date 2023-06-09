#include "Classes/Geometry/Oval.hpp"
#include <cstring>
#include <iostream>

#include "Classes/Base/Application.hpp"

#define DEG2RAD M_PI / 180.0f

Shader* Oval::m_shader = nullptr;

unsigned int Oval::remaining = 0;

// for these functions, I want sine waves
// where the period is 2, offset is variable,
// depending on the color, amp is .5, and
// the y intercept is .5

GLfloat GetRValue(float xpos, float ypos)
{
    return 0.5 * sin((xpos) * M_PI - 2.3) + .5;
}      

GLfloat GetGValue(float xpos, float ypos)
{
    return 0.5 * sin(xpos * M_PI - 4.7) + .5;
}

GLfloat GetBValue(float xpos, float ypos)
{
    return 0.5 * sin((xpos) * M_PI - 7.1) + .5;
}




Oval::Oval()
:IObject(), m_center(0.0f, 0.0f)
{
    // quickly generate a frame so that the buffer has
    // the correct size
    //Frame_SetVertsCorrect(1, 1);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBA);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    if (!m_shader)
    {
        m_shader = new Shader("shaders/Oval/vertex_shader.glsl", "shaders/Oval/fragment_shader.glsl");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    remaining++;
}

Oval::Oval(float width, float height, int centerX, int centerY)
:Oval()
{
    m_center = Point2D(centerX, centerY);
    m_width_from_center = width;
    m_height_from_center = height;
}

Oval::~Oval()
{
    glDeleteBuffers(1, &m_VBA);
    remaining--;
    if (m_shader && !remaining)
    {
        m_shader->DeleteShader();
        m_shader = nullptr;
    }
}

void Oval::Frame_SetVertsCorrect()
{
    // Here we do a lot of math, very quickly
    // In essence, here's the plan (boys)
    // 1) We know where the center is, as well as the height
    //    and width of our ellipse
    // 2) From there, we also have the angle the ellipse is rotated
    //    to
    // 3) Then we use the ellipse formula to generate vertices for
    //    each angle of the ellipse

    // The parameterized equation for an ellipse is as follows:
    // x(t) = Rx * cos(t) * cos(a) - Ry * sin(t) * sin(a) + CenterX
    // y(t) = Rx * cos(t) * sin(a) + Ry * sin(t) * cos(a) + CenterY
    // where:
    //      Rx is the width of the ellipse
    //      Ry is the height of the ellipse
    //      t is the parameter (0 to 2pi)
    //      a is the angle to rotate the ellipse by (counterclockwise, in rads)
    //      (CenterX, CenterY) is the point defining the ellipse's center

    int screenX = Application::CurrentApplication()->Width();
    int screenY = Application::CurrentApplication()->Height();

    float xpos, ypos;
    xpos = m_center.GetXGL(screenX);
    ypos = m_center.GetYGL(screenY);

    vertices.clear();
    vertices.push_back(xpos);
    vertices.push_back(ypos);
    vertices.push_back(0.0f);

    // color
    vertices.push_back(GetRValue(xpos, ypos));
    vertices.push_back(GetGValue(xpos, ypos));
    vertices.push_back(GetBValue(xpos, ypos));

    for (int i = 0; i < 361; i++)
    {
        float xval, yval;
        xval = m_width_from_center * cos(i * DEG2RAD) * cos(angle * DEG2RAD);
        xval += -m_height_from_center * sin(i * DEG2RAD) * sin(angle * DEG2RAD) + m_center.GetXStd();
        yval = m_width_from_center * cos(i * DEG2RAD) * sin(angle * DEG2RAD);
        yval += m_height_from_center * sin(i * DEG2RAD) * cos(angle * DEG2RAD) + m_center.GetYStd();

        Point2D point(xval, yval);

        xpos = point.GetXGL(screenX);
        ypos = point.GetYGL(screenY);

        vertices.push_back(xpos);
        vertices.push_back(ypos);
        vertices.push_back(0.0f);

        vertices.push_back(GetRValue(xpos, ypos));
        vertices.push_back(GetGValue(xpos, ypos));
        vertices.push_back(GetBValue(xpos, ypos));
    }
}

Oval* Oval::CreateInternal(float width, float height, int centerX, int centerY)
{
    return new Oval(width, height, centerX, centerY);
}

void Oval::Update(double deltatime)
{
    Frame_SetVertsCorrect();
}

void Oval::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    
    glBindVertexArray(m_VAO);
    
    m_shader->Use();

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 6);
}