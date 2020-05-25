#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3 &position, const glm::vec3 &lookAtPosition,
               const glm::vec3 &upvec)
    : Front(lookAtPosition), Up(upvec) {

  Position = position;
  WorldUp = upvec;

  update();
}

void Camera::setPosition(const glm::vec3 &position) { Position = position; }

void Camera::setLookAtPosition(const glm::vec3 &lookat) { Front = lookat; }

void Camera::setUpVector(const glm::vec3 &upvec) { Up = upvec; }

glm::mat4 Camera::getCameraViewMatrix() {
  return glm::lookAt(Position, Position + Front, Up);
}

void Camera::OnMouseMovementEvent(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= MoveFactor;
  yoffset *= MoveFactor;

  RotateZ += xoffset;
  RotateX += yoffset;

  // pitch contraints
  if (constrainPitch) {
    if (RotateX > 89.0f)
      RotateX = 89.0f;
    if (RotateX < -89.0f)
      RotateX = -89.0f;
  }

  update();
}

// scroll event
void Camera::OnMouseScrollEvent(float yoffset) { Position += yoffset * Front; }

void Camera::update() {

  glm::vec3 front;
  front.x = cos(glm::radians(RotateZ)) * cos(glm::radians(RotateX));
  front.y = sin(glm::radians(RotateX));
  front.z = sin(glm::radians(RotateZ)) * cos(glm::radians(RotateX));
  Front = glm::normalize(front);

  // calculate Right and Up vector
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}