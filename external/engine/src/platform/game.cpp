#include <iostream>
#include "akai_engine/platform/game.h"
#include <akai_engine/service_locator.h>
#include "glfw_window.h"

Game::Game() : Game("") {}

Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
  initializeServices();
}

Game::~Game() {
  shutdownServices();
}

void Game::Run() {
  ServiceLocator::GetWindow()->OpenWindow({
    .title = _title,
    .width = 800,
    .height = 600,
  });
  while(_running) {
    if(ServiceLocator::GetWindow()->Update()) {
      _running = false;
      continue;
    }

    Update(0.5f);

  }

}

void Game::initializeServices() {
  ServiceLocator::Provide(new WindowGLFW());
}

void Game::shutdownServices() {
  ServiceLocator::ShutdownServices();
}