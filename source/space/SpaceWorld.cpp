#include <string>
#include <gl2d.h>

#include "SpaceWorld.h"
#include "../consts.h"

SpaceWorld::SpaceWorld() {
  this->zoomLevel = 1;
  this->landedOnPlanet = false;
}

void SpaceWorld::generate() {
  // TODO make planets dynamically
  int planets = rand() % 6 + 6;

  for (int i = 0; i < planets; i++) {
    Vector2 pos = {
      rand() % 600 - 400,
      rand() % 600 - 400
    };
    int color = RGB15(rand() % 255, rand() % 255, rand() % 255);

    Planet p = Planet(pos, rand() % 20 + 10, string("Planet") + to_string(i), color);
    this->planets.push_back(p);
  }
}