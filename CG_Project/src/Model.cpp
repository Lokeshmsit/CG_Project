#include "Model.h"
#include "Context.h"
#include <Camera.h>
#include <utils.h>
#include <utils2.h>

glm::mat4 Model::getModel() const { return model; }

void Model::setModel(const glm::mat4 &value) { model = value; }

Model::Model() : mesh(new OBJMeshUV), meshVAO(new MeshVAO) {}

void Model::Render(Context &ctx) {

  glm::mat4 view = glm::mat4(ctx.camera->getCameraViewMatrix());

  glm::mat4 projection =
      glm::perspective(glm::radians(ctx.fov),
                       (float)ctx.width / (float)ctx.height, 0.1f, 1000.0f);

  glm::mat4 mv = view * getModel();
  glm::mat4 mvp = projection * mv;

  // Activate program
  glUseProgram(_shader->getProgram());

  glUniformMatrix4fv(glGetUniformLocation(_shader->getProgram(), "u_mv"), 1,
                     GL_FALSE, &mv[0][0]);

  glUniformMatrix4fv(glGetUniformLocation(_shader->getProgram(), "u_mvp"), 1,
                     GL_FALSE, &mvp[0][0]);

  glUniform1f(glGetUniformLocation(_shader->getProgram(), "u_time"),
              ctx.elapsed_time);

  glUniform3fv(glGetUniformLocation(_shader->getProgram(), "u_light_position"),
               1, &ctx.lightPosition[0]);

  glUniform3fv(glGetUniformLocation(_shader->getProgram(), "u_light_color"), 1,
               ctx.enableLight ? &ctx.lightColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(glGetUniformLocation(_shader->getProgram(), "u_ambient_color"),
               1,
               ctx.enableAmbiant ? &ctx.ambientColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(glGetUniformLocation(_shader->getProgram(), "u_diffuse_color"),
               1,
               ctx.enableDiffuse ? &ctx.diffuseColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(
      glGetUniformLocation(_shader->getProgram(), "u_specular_color"), 1,
      ctx.enableSpecular ? &ctx.specularColor[0] : &glm::vec3(0.0f)[0]);
  glUniform1f(glGetUniformLocation(_shader->getProgram(), "u_specular_power"),
              ctx.specularPower);

  // Draw!
  glBindVertexArray(this->meshVAO->vao);
  // Bind textures
  glDrawElements(GL_TRIANGLES, this->meshVAO->numIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(ctx.defaultVAO);

  glDepthFunc(GL_LEQUAL);
}

void Model::load(const std::string &modelPath) {

  loadUVMesh(modelPath, this->mesh);
  createMeshVAO(*mesh, this->meshVAO);
}

void Model::rotate(float angle, const glm::vec3 &axis) {
  model = glm::rotate(model, glm::radians(angle), axis);
}

void Model::translate(const glm::vec3 &position) {

  model = glm::translate(model, position);
}

void Model::scale(const glm::vec3 &scale) { model = glm::scale(model, scale); }

Shader &Model::getShader() { return *_shader; }

void Model::setShader(Shader *shader) { _shader = shader; }
