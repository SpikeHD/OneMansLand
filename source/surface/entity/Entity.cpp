#include "SpaceEntity.h"

SpaceEntity::SpaceEntity() {
  this->position = {
    0.0f, 0.0f
  };
}

SpaceEntity::SpaceEntity(Vector2 position) {
  this->position = position;
}