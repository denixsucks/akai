#pragma once
#include "platform/window.h"
#include "render/renderer.h"
#include <memory>

class ServiceLocator
{
public:
  static inline const std::unique_ptr<Window>& GetWindow() { return _window; }

  static inline void Provide(Window* window) {
    if(_window != nullptr) return;
    _window = std::unique_ptr<Window>(window);
  }

  static inline const std::unique_ptr<Renderer>& GetRenderer() { return _renderer; }

  static inline void Provide(Renderer* renderer, RendererSettings settings) {
    if (_renderer != nullptr) return;
    _renderer = std::unique_ptr<Renderer>(renderer);
    _renderer->Init(settings);
  }

  static inline void ShutdownServices() {
    shutdownRenderer();
    shutdownWindow();
  }

private:
  static inline std::unique_ptr<Window> _window = nullptr;
  static inline std::unique_ptr<Renderer> _renderer = nullptr;
  static inline void shutdownWindow() {
    _window.reset();
    _window = nullptr;
  }
  static inline void shutdownRenderer() {
    if (!_renderer) return;
    _renderer->Shutdown();
    _renderer = nullptr;
  }
};