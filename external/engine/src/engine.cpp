#include <iostream>
#include <akai_engine/engine.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <akai_engine/service_locator.h>
#include "platform/glfw_window.h"

void Engine::Init()
{
  std::cout << "Initializing window." << "\n";
  ServiceLocator::Provide(new WindowGLFW());
}