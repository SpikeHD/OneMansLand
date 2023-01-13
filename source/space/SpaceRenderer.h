#ifndef SPC_RENDER_H
#define SPC_RENDER_H

#include "SpaceWorld.h"
#include "entity/SpacePlayer.h"
#include "entity/Ship.h"

struct SpaceEntityScreenPos {
  float xMin;
  float yMin;
  float xMax;
  float yMax;
};

void spaceRender(SpaceWorld&, SpacePlayer&);
SpaceEntityScreenPos SpaceEntityScreenPosition(SpaceWorld&, SpaceEntity&, SpacePlayer&);

#endif