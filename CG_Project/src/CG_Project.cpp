// Assignment 3, Part 1 and 2
//
// Modify this file according to the lab instructions.
// test

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "Terrain.h"
#include <Model.h>
#include <SkyDome.h>
#include <Skybox.h>

#include <algorithm>
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <Context.h>
#include <IOEvent.h>
#include <utils.h>
#include <utils2.h>

void init(Context &ctx) {

  /*-------terrain -------*/
  Terrain *terrain = new Terrain;
  terrain->load(modelDir() + "red-sculpted-plains-terrain/source/"
                             "RedSculptedPlains Mesh Output/RedSculptedPlains "
                             "Mesh Output 2.obj");
  Shader *shader =
      new Shader(shaderDir() + "mesh.vert", shaderDir() + "mesh.frag");
  terrain->setShader(shader);
  terrain->scale(glm::vec3(700.f, 700.f, 700.f));
  terrain->rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));

  ctx.terrain = terrain;

  /*-------camera -------*/
  ctx.camera = new Camera(glm::vec3(0.0f, 60.0f, 50.0f),
                          glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0));

  ctx.skydome = new SkyDome;
  Shader *shaderSkyDome =
      new Shader(shaderDir() + "SkyDome.vert", shaderDir() + "SkyDome.frag");

  ctx.skydome->load(modelDir() + "Skydome3D/Skydome.obj");
  ctx.skydome->scale(glm::vec3(3.f, 3.f, 3.f));
  ctx.skydome->translate(glm::vec3(0.0f, -25.f, 0.f));
  ctx.skydome->setShader(shaderSkyDome);

  ctx.projection =
      glm::perspective(glm::radians(ctx.fov),
                       (float)ctx.width / (float)ctx.height, 0.1f, 1000.0f);
}

void display(Context &ctx) {

  glClearColor(ctx.backgroudColor[0], ctx.backgroudColor[1],
               ctx.backgroudColor[2], ctx.backgroudColor[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); // ensures that polygons overlap correctly

  ctx.terrain->Render(ctx);
  ctx.skydome->Render(ctx);
}

void drawImGuiControls(Context &ctx) {

  ImGui::Begin("Settings");

  if (ImGui::CollapsingHeader("Lighting", true)) {
    ImGui::ColorEdit3("Light Color", &ctx.lightColor[0]);
    ImGui::Checkbox("Light Enabled", &ctx.enableLight);
    ImGui::ColorEdit3("Ambient Light", &ctx.ambientColor[0]);
    ImGui::Checkbox("Ambiant Enabled", &ctx.enableAmbiant);
    ImGui::ColorEdit3("Specular Light", &ctx.specularColor[0]);
  }



  ImGui::End();
}

int main(void) {
  Context ctx;

  // Create a GLFW window
  glfwSetErrorCallback(errorCallback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

  ctx.width = mode->width;
  ctx.height = mode->height;
  ctx.aspect = float(ctx.width) / float(ctx.height);
  ctx.window =
      glfwCreateWindow(ctx.width, ctx.height, "CG Project", monitor, nullptr);
  glfwMakeContextCurrent(ctx.window);
  glfwSetWindowUserPointer(ctx.window, &ctx);
  glfwSetKeyCallback(ctx.window, keyCallback);
  glfwSetCharCallback(ctx.window, charCallback);
  glfwSetMouseButtonCallback(ctx.window, mouseButtonCallback);
  glfwSetScrollCallback(ctx.window, scrollCallback);
  glfwSetCursorPosCallback(ctx.window, cursorPosCallback);
  glfwSetFramebufferSizeCallback(ctx.window, resizeCallback);

  // Load OpenGL functions
  glewExperimental = true;
  GLenum status = glewInit();
  if (status != GLEW_OK) {
    std::cerr << "Error: " << glewGetErrorString(status) << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Initialize GUI
  ImGui_ImplGlfwGL3_Init(ctx.window, false /*do not install callbacks*/);

  // Initialize rendering
  glGenVertexArrays(1, &ctx.defaultVAO);
  glBindVertexArray(ctx.defaultVAO);
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  init(ctx);

  // Start rendering loop
  while (!glfwWindowShouldClose(ctx.window)) {
    glfwPollEvents();
    ctx.elapsed_time = glfwGetTime();
    ImGui_ImplGlfwGL3_NewFrame();
    drawImGuiControls(ctx);
    display(ctx);
    ImGui::Render();
    glfwSwapBuffers(ctx.window);
  }

  // Shutdown
  glfwDestroyWindow(ctx.window);
  glfwTerminate();
  std::exit(EXIT_SUCCESS);
}
