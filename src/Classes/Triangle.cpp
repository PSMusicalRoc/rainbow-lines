#include "Classes/Triangle.hpp"
#include <iostream>

GLuint Triangle::vertshader = 0;
GLuint Triangle::fragshader = 0;
GLuint Triangle::program = 0;

Triangle::Triangle()
{
    vertices = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBA);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (!program)
    {
        const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

        const char* fragShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n\n"

        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

        vertshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertshader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertshader);

#ifdef ROC_DEBUG
        GLint success;
        char infoLog[512];

        glGetShaderiv(vertshader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertshader, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;
        }
#endif

        fragshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragshader, 1, &fragShaderSource, NULL);
        glCompileShader(fragshader);

#ifdef ROC_DEBUG
        glGetShaderiv(fragshader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragshader, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;
        }
#endif

        program = glCreateProgram();
        glAttachShader(program, vertshader);
        glAttachShader(program, fragshader);
        glLinkProgram(program);

#ifdef ROC_DEBUG
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << infoLog << std::endl;
        }
#endif

        glDeleteShader(vertshader);
        glDeleteShader(fragshader);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::Render()
{
    glBindVertexArray(m_VAO);
    
    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}