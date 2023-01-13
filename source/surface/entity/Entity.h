#ifndef SUR_SpaceEntity_H
#define SUR_SpaceEntity_H

#include "../../Vector.h"

class SpaceEntity {
  public:
    SpaceEntity(Vector2);
    SpaceEntity();

  private:
    Vector2 position;
};

#endif