#include "Planet.h"
#include <vector>

#ifndef SPC_WORLD_H
#define SPC_WORLD_H

class SpaceWorld {
  public:
    std::vector<Planet> planets;

    SpaceWorld();

    void generate();
};

#endif