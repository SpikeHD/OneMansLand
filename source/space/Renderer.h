#ifndef SPC_RENDER_H
#define SPC_RENDER_H

#include "SpaceWorld.h"
#include "SpaceEntity/SpacePlayer.h"
#include "SpaceEntity/Ship.h"

struct SpaceEntityScreenPos {
  float xMin;
  float yMin;
  float xMax;
  float yMax;
};

void render(SpaceWorld&, SpacePlayer&);
SpaceEntityScreenPos SpaceEntityScreenPosition(SpaceWorld&, SpaceEntity&, SpacePlayer&);

#endif