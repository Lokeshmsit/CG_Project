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

// Processes input received from a mouse input system. Expects the offset value
// in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= MouseMove;
  yoffset *= MouseMove;

  RotateZ += xoffset;
  RotateX += yoffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (RotateX > 89.0f)
      RotateX = 89.0f;
    if (RotateX < -89.0f)
      RotateX = -89.0f;
  }

  // Update Front, Right and Up Vectors using the updated Euler angles
  update();
}

// Processes input received from a mouse scroll-wheel event. Only requires input
// on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) { Position += yoffset * Front; }

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::update() {
  // Calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(RotateZ)) * cos(glm::radians(RotateX));
  front.y = sin(glm::radians(RotateX));
  front.z = sin(glm::radians(RotateZ)) * cos(glm::radians(RotateX));
  Front = glm::normalize(front);
  // Also re-calculate the Right and Up vector
  Right = glm::normalize(glm::cross(Front, WorldUp)); // Normalize the vectors,
                                                      // because their length
                                                      // gets closer to 0 the
                                                      // more you look up or
                                                      // down which results in
                                                      // slower movement.
  Up = glm::normalize(glm::cross(Right, Front));

  // std::cout << Up.x << ", " << Up.y << ", " << Up.z << std::endl;
}
