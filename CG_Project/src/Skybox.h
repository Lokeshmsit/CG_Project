#ifndef SKYBOX_H
#define SKYBOX_H
#include <GL/glew.h>
#include <Shader.h>

struct Context;

struct Context;
struct OBJMesh;
struct OBJMeshUV;
struct MeshVAO;

class Skybox {

  MeshVAO *meshVAO;
  GLuint texture;
  Shader *shader;

public:
  Skybox(const std::string &dirPath);
  void Render(Context &ctx);

  Shader &getShader();
  void setShader(Shader *value);
};

#endif // SKYBOX_H
