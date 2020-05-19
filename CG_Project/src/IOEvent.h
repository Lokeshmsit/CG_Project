#pragma once

#include <Context.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <utils2.h>
void mouseButtonPressed(Context *ctx, int button, int x, int y);

void mouseButtonReleased(Context *ctx, int button, int x, int y);

void moveTrackball(Context *ctx, int x, int y);

void errorCallback(int /*error*/, const char *description);

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void charCallback(GLFWwindow *window, unsigned int codepoint);

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void cursorPosCallback(GLFWwindow *window, double x, double y);
void resizeCallback(GLFWwindow *window, int width, int height);
void scrollCallback(GLFWwindow *window, double x, double y);
