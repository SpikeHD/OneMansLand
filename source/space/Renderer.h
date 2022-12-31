#include "SpaceWorld.h"
#include "entity/SpacePlayer.h"

#ifndef SPC_RENDER_H
#define SPC_RENDER_H

struct PlanetPosition {
  float xMin;
  float yMin;
  float xMax;
  float yMax;
};

void render(SpaceWorld, SpacePlayer);
PlanetPosition planetScreenPosition(SpaceWorld, Planet, SpacePlayer);

#endif