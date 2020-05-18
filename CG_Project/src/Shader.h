#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>
#include <utils.h>

class Shader {

  GLuint program;

public:
  Shader(const std::string &vertexShaderFilename,
         const std::string &fragmentShaderFilename);
  GLuint &getProgram();
  void setProgram(const GLuint &value);
};

#endif // SHADER_H
