#ifndef MODEL_H
#define MODEL_H

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

class Model {

  OBJMeshUV *mesh;
  MeshVAO *meshVAO;
  glm::mat4 model;
  Shader *_shader;
  GLuint shaderProgram;

public:
  Model();

  virtual void load(const std::string &modelPath);

  void rotate(float angle, const glm::vec3 &axis);
  void translate(const glm::vec3 &position);
  void scale(const glm::vec3 &scale);

  virtual void Render(Context &ctx);

  Shader &getShader();
  void setShader(Shader *value);

  OBJMeshUV *getMesh() { return mesh; }
  MeshVAO *getMeshVBO() { return meshVAO; }
};

#endif // MODEL_H
