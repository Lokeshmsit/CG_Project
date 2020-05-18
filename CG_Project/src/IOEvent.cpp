#include "IOEvent.h"
#include "Camera.h"

float lastX;
float lastY;
bool firstMouse = true;

void mouseButtonPressed(Context *ctx, int button, int x, int y) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    ctx->trackball->center = glm::vec2(x, y);
    // trackballStartTracking(*ctx->trackball, glm::vec2(x, y));
  }
}

void mouseButtonReleased(Context *ctx, int button, int x, int y) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    // trackballStopTracking(*ctx->trackball);
  }
}

void moveTrackball(Context *ctx, int x, int y) {
  if (ctx->trackball->tracking) {
    // trackballMove(*ctx->trackball, glm::vec2(x, y));
  }

  if (firstMouse) {
    lastX = x;
    lastY = y;
    firstMouse = false;
  }

  float xoffset = x - lastX;
  float yoffset = lastY - y;

  lastX = x;
  lastY = y;

  ctx->camera->ProcessMouseMovement(xoffset, yoffset);
}

void errorCallback(int /*error*/, const char *description) {
  std::cerr << description << std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  // Forward event to GUI
  ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
  if (ImGui::GetIO().WantCaptureKeyboard) {
    return;
  } // Skip other handling

  Context *ctx = static_cast<Context *>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    // reloadShaders(ctx);
  }
}

void charCallback(GLFWwindow *window, unsigned int codepoint) {
  // Forward event to GUI
  ImGui_ImplGlfwGL3_CharCallback(window, codepoint);
  if (ImGui::GetIO().WantTextInput) {
    return;
  } // Skip other handling
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  // Forward event to GUI
  ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
  if (ImGui::GetIO().WantCaptureMouse) {
    return;
  } // Skip other handling

  double x, y;
  glfwGetCursorPos(window, &x, &y);

  Context *ctx = static_cast<Context *>(glfwGetWindowUserPointer(window));
  if (action == GLFW_PRESS) {
    mouseButtonPressed(ctx, button, x, y);
  } else {
    mouseButtonReleased(ctx, button, x, y);
  }
}

void cursorPosCallback(GLFWwindow *window, double x, double y) {
  if (ImGui::GetIO().WantCaptureMouse) {
    return;
  } // Skip other handling

  Context *ctx = static_cast<Context *>(glfwGetWindowUserPointer(window));
  moveTrackball(ctx, x, y);
}

void resizeCallback(GLFWwindow *window, int width, int height) {
  Context *ctx = static_cast<Context *>(glfwGetWindowUserPointer(window));
  ctx->width = width;
  ctx->height = height;
  ctx->aspect = float(width) / float(height);
  ctx->trackball->radius = double(std::min(width, height)) / 2.0;
  ctx->trackball->center = glm::vec2(width, height) / 2.0f;
  glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow *window, double x, double y) {

  Context *ctx = static_cast<Context *>(glfwGetWindowUserPointer(window));

  // ctx->fov += (float)ctx->zoomFactorPerspective * y;

  ctx->camera->ProcessMouseScroll(y);
}
