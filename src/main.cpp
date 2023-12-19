#include <iostream>
#include <akai_engine/platform/entry_point.h>

class TestGame : public Game {
public:
  explicit TestGame(std::string title) : Game(std::move(title)) {
  };
protected:
  void Update(float deltaTime) override {
  }
};

Game* CreateGame() {
  return new TestGame("Game Name!");
}
