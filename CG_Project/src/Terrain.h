#pragma once

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

struct Context;
struct OBJMesh;
struct OBJMeshUV;
struct MeshVAO;

class Terrain {

  OBJMeshUV *mesh;
  MeshVAO *meshVAO;
  glm::mat4 model;
  Shader *_shader;
  GLuint shaderProgram;

public:
  Terrain();

  void load(const std::string &modelPath);
  void Render(Context &ctx);
  void rotate(float angle, const glm::vec3 &axis);
  void translate(const glm::vec3 &position);
  void scale(const glm::vec3 &scale);

  Shader &getShader();
  void setShader(Shader *value);
};
