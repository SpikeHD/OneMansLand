#include "./SpaceWorld.h"
#include "../consts.h"

SpaceWorld::SpaceWorld() {

}

void SpaceWorld::generate() {
  // TODO maake planets dynamically
  Vector2 pPos = { SCR_MAX_X / 2, SCR_MAX_Y / 2 };
  Planet p = Planet(pPos, 20, "Planet 1");

  this->planets.push_back(p);
}