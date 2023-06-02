#ifndef _ROC_SHADER_GL_HPP_
#define _ROC_SHADER_GL_HPP_

#include <glad/gl.h>
#include <string>

GLuint LoadShader(const std::string& vertshader_file, const std::string& fragshader_file);

#endif