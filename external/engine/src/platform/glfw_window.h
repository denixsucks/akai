#pragma once

#include <akai_engine/platform/window.h>
#include <GLFW/glfw3.h>

class WindowGLFW : public Window {
public:
  WindowGLFW();
  virtual void OpenWindow() override;
  virtual bool Update() override;

private:
  GLFWwindow* _window;
};