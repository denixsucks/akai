#include <iostream>
#include <akai_engine/platform/game.h>
#include <akai_engine/service_locator.h>
#include "render/vulkan/vulkan_renderer.h"
#include "glfw_window.h"

Game::Game() : Game("") {}

Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
  initializeServices();
}

Game::~Game() {
  shutdownServices();
}

void Game::Run() {
  while(_running) {
    if(ServiceLocator::GetWindow()->Update()) {
      _running = false;
      continue;
    }

    Update(0.5f);

    ServiceLocator::GetRenderer()->RenderFrame(); // render a frame !

  }

}

void Game::initializeServices() {
  ServiceLocator::Provide(new WindowGLFW());
  RendererSettings settings {
    .ApplicationName = _title,
  };

  ServiceLocator::GetWindow()->OpenWindow({
    .title = _title,
    .width = 800,
    .height = 600,
  });

  ServiceLocator::Provide(new VulkanRenderer(), settings);
}

void Game::shutdownServices() {
  ServiceLocator::ShutdownServices();
}