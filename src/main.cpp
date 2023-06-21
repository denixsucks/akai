#include <iostream>
#include <akai_engine/engine.h>
#include <akai_engine/service_locator.h>

int main()
{
  Engine::Init();
  ServiceLocator::GetWindow()->OpenWindow();
  while(ServiceLocator::GetWindow()->Update())
  {
    
  }
  return 0;
}