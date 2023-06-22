#pragma once
#include <memory>
#include <akai_engine/platform/window.h>

class ServiceLocator
{
public:
  static inline const std::unique_ptr<Window>& GetWindow() { return _window; }
  
  static inline void Provide(Window* window) {
    if(_window != nullptr) return;
    _window = std::unique_ptr<Window>(window);
  }

  static inline void ShutdownServices() {
    shutdownWindow();
  }

private:
  static inline std::unique_ptr<Window> _window = nullptr;
  static inline void shutdownWindow() {
    _window.reset();
    _window = nullptr;
  }
};