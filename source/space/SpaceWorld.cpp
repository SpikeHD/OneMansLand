#include "./SpaceWorld.h"
#include "../consts.h"

SpaceWorld::SpaceWorld() {
  this->zoomLevel = 1;
}

void SpaceWorld::generate() {
  // TODO maake planets dynamically
  Vector2 pPos = { 50, 50 };
  Planet p = Planet(pPos, 20, "Planet 1");

  this->planets.push_back(p);
}