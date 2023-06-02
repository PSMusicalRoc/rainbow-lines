#include "Roc_GL/Shader.hpp"
#include <fstream>
#include <iostream>

GLuint LoadShader(const std::string& vertshader_file, const std::string& fragshader_file)
{
    std::ifstream vsh_file(vertshader_file);
    if (!vsh_file.is_open())
    {
        std::cerr << "Could not find file " << vertshader_file << std::endl;
        std::cerr << "Please check your path." << std::endl;
        return 0;
    }

    std::string inLine, vshad_source;
    while (std::getline(vsh_file, inLine))
    {
        vshad_source += inLine + "\n";
    }
    vsh_file.close();

    std::ifstream fsh_file(fragshader_file);
    if (!fsh_file.is_open())
    {
        std::cerr << "Could not find file " << fragshader_file << std::endl;
        std::cerr << "Please check your path." << std::endl;
        return 0;
    }

    std::string fshad_source;
    while (std::getline(fsh_file, inLine))
    {
        fshad_source += inLine + "\n";
    }
    fsh_file.close();

    const char* vsh_cstr = vshad_source.c_str();

    GLuint vertshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertshader, 1, &vsh_cstr, NULL);
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

    const char* fsh_cstr = fshad_source.c_str();

    GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragshader, 1, &fsh_cstr, NULL);
    glCompileShader(fragshader);

#ifdef ROC_DEBUG
    glGetShaderiv(fragshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragshader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
#endif

    GLuint program = glCreateProgram();
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

    return program;
}