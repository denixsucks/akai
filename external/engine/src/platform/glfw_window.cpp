#include "glfw_window.h"

WindowGLFW::WindowGLFW()
{
  _window = nullptr;
}

void WindowGLFW::OpenWindow()
{
  glfwInit();
  _window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
}

bool WindowGLFW::Update()
{
  glfwPollEvents();
  return glfwWindowShouldClose(_window);
}
