#include <iostream>
#include "glfw_window.h"

WindowGLFW::WindowGLFW()
{
  _window = nullptr;
}

void WindowGLFW::OpenWindow(WindowData data)
{
  glfwInit();
  _window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
}

bool WindowGLFW::Update()
{
  glfwPollEvents();
  return glfwWindowShouldClose(_window);
}
