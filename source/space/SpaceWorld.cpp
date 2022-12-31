#include <string>

#include "./SpaceWorld.h"
#include "../consts.h"

SpaceWorld::SpaceWorld() {
  this->zoomLevel = 1;
}

void SpaceWorld::generate() {
  // TODO make planets dynamically
  int planets = rand() % 6 + 6;

  for (int i = 0; i < planets; i++) {
    Vector2 pos = {
      rand() % 600 - 400,
      rand() % 600 - 400
    };

    Planet p = Planet(pos, rand() % 20 + 10, string("Planet") + to_string(i));
    this->planets.push_back(p);
  }
}