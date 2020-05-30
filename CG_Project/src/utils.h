#pragma once

#include <GL/glew.h>
#include <lodepng.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// The attribute locations we will use in the vertex shader
enum AttributeLocation {
  POSITION = 0,
  NORMAL = 1,
  TEXTURE = 2,
  TANGENT = 3,
  BITANGENT = 4
};

struct MeshVAO {
  GLuint vao;
  GLuint vertexVBO;
  GLuint normalVBO;
  GLuint indexVBO;
  GLuint textureVBO;
  GLuint tangentVBO;
  GLuint biTangentVBO;

  std::map<std::string, GLuint> textureMap;

  int numVertices;
  int numIndices;
};

// Returns the value of an environment variable
std::string getEnvVar(const std::string &name);

// Returns the absolute path to the shader directory
std::string shaderDir(void);

// Returns the absolute path to the 3D model directory
std::string modelDir(void);

// Returns the absolute path to the cubemap texture directory
std::string cubemapDir(void);
std::string readShaderSource(const std::string &filename);
void showShaderInfoLog(GLuint shader);
void showProgramInfoLog(GLuint program);

GLuint loadShaderProgram(const std::string &vertexShaderFilename,
                         const std::string &fragmentShaderFilename);
/*
void reloadShaders(Context *ctx) {
  glDeleteProgram(ctx->program);
  ctx->program =
      loadShaderProgram(shaderDir() + "mesh.vert", shaderDir() + "mesh.frag");
}
*/
GLuint load2DTexture(const std::string &filename);

// Load cubemap texture and let OpenGL generate a mipmap chain
GLuint loadCubemap(const std::string &dirname);

// Load cubemap with pre-computed mipmap chain
GLuint loadCubemapMipmap(const std::string &dirname);
