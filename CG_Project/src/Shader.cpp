#include "Shader.h"

GLuint &Shader::getProgram() { return program; }

void Shader::setProgram(const GLuint &value) { program = value; }

Shader::Shader(const std::string &vertexShaderFilename,
               const std::string &fragmentShaderFilename) {
  program = loadShaderProgram(vertexShaderFilename, fragmentShaderFilename);
}
