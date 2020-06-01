#include "SkyDome.h"
#include "Context.h"
#include <Camera.h>
#include <utils.h>
#include <utils2.h>

SkyDome::SkyDome() {}

void SkyDome::load(const std::string &modelPath) {

  loadUVMesh(modelPath, getMesh());
  createUVMeshVAO(*getMesh(), getMeshVBO());
  GLuint sky_texture = load2DTexture(modelDir() + "Skydome3D/Skydome.png");

  getMeshVBO()->textureMap.insert(
      std::pair<std::string, GLuint>("Sky_Texture", sky_texture));
}

void SkyDome::Render(Context &ctx) {

  glm::mat4 view = glm::mat4(ctx.camera->getCameraViewMatrix());

  glm::mat4 projection =
      glm::perspective(glm::radians(ctx.fov),
                       (float)ctx.width / (float)ctx.height, 0.1f, 1000.0f);

  glm::mat4 mv = view * getModel();
  glm::mat4 mvp = projection * mv;

  // Activate program
  glUseProgram(getShader().getProgram());

  glUniformMatrix4fv(glGetUniformLocation(getShader().getProgram(), "u_mv"), 1,
      GL_FALSE, &mv[0][0]);

  glUniformMatrix4fv(glGetUniformLocation(getShader().getProgram(), "u_mvp"), 1,
      GL_FALSE, &mvp[0][0]);

  glUniform3fv(glGetUniformLocation(getShader().getProgram(), "u_light_position"), 1, 
      &ctx.lightPosition[0]);

  glUniform3fv(glGetUniformLocation(getShader().getProgram(), "u_light_color"), 1, 
      ctx.enableLight ? &ctx.lightColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(glGetUniformLocation(getShader().getProgram(), "u_ambient_color"), 1, 
      ctx.enableAmbiant ? &ctx.ambientColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(
      glGetUniformLocation(getShader().getProgram(), "u_diffuse_color"), 1,
      ctx.enableDiffuse ? &ctx.diffuseColor[0] : &glm::vec3(0.0f)[0]);

  glUniform3fv(
      glGetUniformLocation(getShader().getProgram(), "u_specular_color"), 1, 
      &ctx.specularColor[0]);
      
  glUniform1f(
      glGetUniformLocation(getShader().getProgram(), "u_specular_power"),
      ctx.specularPower);

  glUniform1i(glGetUniformLocation(getShader().getProgram(), "tex0"), 0);

  // Draw!
  glBindVertexArray(getMeshVBO()->vao);
  // Bind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, getMeshVBO()->textureMap["Sky_Texture"]);

  glDrawElements(GL_TRIANGLES, getMeshVBO()->numIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(ctx.defaultVAO);

  glDepthFunc(GL_LEQUAL);
}
