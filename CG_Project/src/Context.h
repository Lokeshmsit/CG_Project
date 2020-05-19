#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
class Terrain;
class Camera;
struct Trackball;
class Skybox;
class Model;
// Struct for resources and state
struct Context {

  //---- Window
  int width;
  int height;
  float aspect;
  GLFWwindow *window;
  GLuint program;
  Trackball *trackball;

  //---actors/mesh and opengl objects
  GLuint defaultVAO;
  GLuint cubemap;
  Terrain *terrain;
  Camera *camera;
  Skybox *skybox;
  Model *skydome;
  //--add your own here

  //-----Rendering -----
  glm::mat4 projection;
  glm::vec4 lightColor = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec3 lightPosition = glm::vec3{1.0, 1.0, 1.0};
  bool enableLight = true;

  glm::vec3 ambientColor = glm::vec3(0.06, 0.6, 0.6);
  bool enableAmbiant = true;
  glm::vec3 diffuseColor = glm::vec3{0.6, 0.6, 0.6};
  bool enableDiffuse = true;
  glm::vec3 specularColor = glm::vec3(0.04, 0.04, 0.04);
  bool enableSpecular = true;
  float specularPower = 60.0;

  glm::vec4 backgroudColor = glm::vec4(0.2, 0.2, 0.2, 1.0);

  bool enablePerspective = false;
  bool ortho = true;
  float zoomFactorOrtho = 0.15;
  float zoomFactorPerspective = 5.0f;
  float zoom = 0.f;
  float fov = 45.0f;
  float elapsed_time;
};

#endif // CONTEXT_H
