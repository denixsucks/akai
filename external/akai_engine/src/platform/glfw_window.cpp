#include <iostream>
#include "glfw_window.h"

WindowGLFW::WindowGLFW() {
  _window = nullptr;
}

void WindowGLFW::OpenWindow(WindowData data) {
  glfwInit();

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  _window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
}

std::pair<int, int> WindowGLFW::GetWindowExtents() {
  int width, height;
  glfwGetFramebufferSize(_window, &width, &height);
  return {width, height};
}

bool WindowGLFW::Update() {
  glfwPollEvents();
  return glfwWindowShouldClose(_window);
}

void WindowGLFW::RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) {
  try {
    auto vkInstance = std::any_cast<VkInstance>(args[SurfaceArgs::INSTANCE]);
    auto *allocationCallbacks = args[SurfaceArgs::ALLOCATORS].has_value() ? std::any_cast<VkAllocationCallbacks *>(args[SurfaceArgs::ALLOCATORS]) : nullptr; // could be nullptr
    auto *outSurface = std::any_cast<VkSurfaceKHR *>(args[SurfaceArgs::OUT_SURFACE]);

    if(vkInstance == VK_NULL_HANDLE) {
      throw std::runtime_error("There is no instance.");
    }

    if (glfwCreateWindowSurface(vkInstance, _window, allocationCallbacks, outSurface) != VK_SUCCESS ) {
      throw std::runtime_error("Failed to create window surface.");
    }
  }
  catch (std::bad_any_cast& e) { std::cout << "Failed to cast window surface args: " << e.what() << std::endl; }
}