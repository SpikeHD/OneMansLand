#include "SpaceWorld.h"
#include "entity/Player.h"

#ifndef SPC_RENDER_H
#define SPC_RENDER_H

struct PlanetPosition {
  float xMin;
  float yMin;
  float xMax;
  float yMax;
};

void render(SpaceWorld, Player);
PlanetPosition planetScreenPosition(SpaceWorld, Planet, Player);

#endif