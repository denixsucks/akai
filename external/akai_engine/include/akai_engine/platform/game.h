#pragma once
#include <string>

class Game {
public:
  Game();
  explicit Game(std::string windowTitle);
  ~Game();

  void Run();

  std::string _title;

protected:
  virtual void Update(float deltaTime) {};
  virtual void PhysicsUpdate(float deltaTime) {};

private:
  void initializeServices();
  void shutdownServices();

  bool _running;
};

extern Game* CreateGame();