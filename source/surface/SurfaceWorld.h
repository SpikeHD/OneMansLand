#ifndef SUR_WORLD_H
#define SUR_WORLD_H

#include <vector>
#include "Tile.h"

class SurfaceWorld {
  public:
    std::vector<std::vector<Tile>> tiles;

    SurfaceWorld();
};

#endif