#include "Skybox.h"
#include <Camera.h>
#include <Context.h>
#include <utils.h>
#include <utils2.h>

Skybox::Skybox(const std::string &dirPath) : meshVAO(new MeshVAO) {

  float skyboxVertices[] = {
      // positions
      -1000.f, 1000.f,  -1000.f, -1000.f, -1000.f, -1000.f,
      1000.f,  -1000.f, -1000.f, 1000.f,  -1000.f, -1000.f,
      1000.f,  1000.f,  -1000.f, -1000.f, 1000.f,  -1000.f,

      -1000.f, -1000.f, 1000.f,  -1000.f, -1000.f, -1000.f,
      -1000.f, 1000.f,  -1000.f, -1000.f, 1000.f,  -1000.f,
      -1000.f, 1000.f,  1000.f,  -1000.f, -1000.f, 1000.f,

      1000.f,  -1000.f, -1000.f, 1000.f,  -1000.f, 1000.f,
      1000.f,  1000.f,  1000.f,  1000.f,  1000.f,  1000.f,
      1000.f,  1000.f,  -1000.f, 1000.f,  -1000.f, -1000.f,

      -1000.f, -1000.f, 1000.f,  -1000.f, 1000.f,  1000.f,
      1000.f,  1000.f,  1000.f,  1000.f,  1000.f,  1000.f,
      1000.f,  -1000.f, 1000.f,  -1000.f, -1000.f, 1000.f,

      -1000.f, 1000.f,  -1000.f, 1000.f,  1000.f,  -1000.f,
      1000.f,  1000.f,  1000.f,  1000.f,  1000.f,  1000.f,
      -1000.f, 1000.f,  1000.f,  -1000.f, 1000.f,  -1000.f,

      -1000.f, -1000.f, -1000.f, -1000.f, -1000.f, 1000.f,
      1000.f,  -1000.f, -1000.f, 1000.f,  -1000.f, -1000.f,
      -1000.f, -1000.f, 1000.f,  1000.f,  -1000.f, 1000.f};

  glGenVertexArrays(1, &meshVAO->vao);
  glGenBuffers(1, &meshVAO->vertexVBO);
  glBindVertexArray(meshVAO->vao);
  glBindBuffer(GL_ARRAY_BUFFER, meshVAO->vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  texture = loadCubemap(dirPath);
}

void Skybox::Render(Context &ctx) {

  glUseProgram(shader->getProgram());

  glm::mat4 projection =
      glm::perspective(glm::radians(ctx.fov),
                       (float)ctx.width / (float)ctx.height, 0.1f, 10000.0f);

  glm::mat4 view = glm::mat4(ctx.camera->getCameraViewMatrix());
  glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "u_v"), 1,
                     GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "u_p"), 1,
                     GL_FALSE, &projection[0][0]);
  // skybox cube
  glBindVertexArray(meshVAO->vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
}

Shader &Skybox::getShader() { return *shader; }

void Skybox::setShader(Shader *value) { shader = value; }
