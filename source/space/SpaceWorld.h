#include "entity/Planet.h"
#include <vector>

#ifndef SPC_WORLD_H
#define SPC_WORLD_H

class SpaceWorld {
  public:
    float zoomLevel;
    bool landedOnPlanet;

    std::vector<Planet> planets;

    SpaceWorld();

    void generate();
};

#endif