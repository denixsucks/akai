#pragma once
#include <iostream>
#include <akai_engine/service_locator.h>
#include <akai_engine/platform/game.h>


int main()
{
  auto* game = CreateGame();
  game->Run();
  delete game;
}