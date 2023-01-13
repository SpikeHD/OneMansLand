#include "SurfaceEntity.h"

SurfaceEntity::SurfaceEntity() {
  this->position = {
    0.0f, 0.0f
  };
}

SurfaceEntity::SurfaceEntity(Vector2 position) {
  this->position = position;
}