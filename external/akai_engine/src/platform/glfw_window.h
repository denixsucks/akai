#pragma once

#include <akai_engine/platform/window.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


class WindowGLFW : public Window {
public:
  WindowGLFW();
  void OpenWindow(WindowData data) override;
  bool Update() override;
  std::pair<int, int> GetWindowExtents() override;
  void RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any>) override;

private:
  GLFWwindow* _window;
};