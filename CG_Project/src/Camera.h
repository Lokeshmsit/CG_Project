#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to
// stay away from window-system specific input methods
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 1.5f;

class Camera {

  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;

  glm::vec3 Right;
  glm::vec3 WorldUp;
  // Euler Angles
  float Yaw;
  float Pitch;
  // Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

public:
  Camera(const glm::vec3 &position, const glm::vec3 &lookAtPosition,
         const glm::vec3 &upvec);
  void setPosition(const glm::vec3 &position);
  void setLookAtPosition(const glm::vec3 &lookat);
  void setUpVector(const glm::vec3 &upvec);

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseScroll(float yoffset);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);
  // Calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors();

  glm::mat4 getCameraViewMatrix();
  void setCameraViewMatrix(const glm::mat4 &view_matrix);
};

#endif // CAMERA_H
