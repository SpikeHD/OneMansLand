#ifndef SUR_ENTITY_H
#define SUR_ENTITY_H

#include "../../Vector.h"

class SurfaceEntity {
  public:
    SurfaceEntity(Vector2);
    SurfaceEntity();

  private:
    Vector2 position;
};

#endif