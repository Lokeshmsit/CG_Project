#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;

  glm::vec3 Right;
  glm::vec3 WorldUp;

  float RotateZ = -90.0f;
  float RotateX = 0.0f;
  float MoveFactor = 0.2f;

public:
  Camera(const glm::vec3 &position, const glm::vec3 &lookAtPosition,
         const glm::vec3 &upvec);
  void setPosition(const glm::vec3 &position);
  void setLookAtPosition(const glm::vec3 &lookat);
  void setUpVector(const glm::vec3 &upvec);

  void OnMouseScrollEvent(float yoffset);
  void OnMouseMovementEvent(float xoffset, float yoffset,
                            bool constrain_Pitch = true);

  void update();

  glm::mat4 getCameraViewMatrix();
  void setCameraViewMatrix(const glm::mat4 &view_matrix);
};
