#include <cmath>

#include "Planet.h"
#include "SpaceEntity.h"

Planet::Planet(Vector2 position, float size, string name, int color) {
  this->position = position;
  this->size = {
    size,
    size
  };
  this->name = name;
  this->color = color;
}

void Planet::generate() {
  // TODO assign seed based on some calculation
}

int Planet::gravitationalFieldSize() {
  // Based on the size, calculate the field size
  // This is just shittily calculated for now
  return this->size.x * 2;
}

void Planet::pull(SpaceEntity &SpaceEntity) {
  bool inField = this->isInField(SpaceEntity);
  float pullforce = this->pullForce(SpaceEntity);

  if (!inField) pullforce = 0;

  float xPullforce = pullforce;
  float yPullforce = pullforce;

  if (SpaceEntity.getPosition().x > this->position.x) xPullforce = -pullforce;
  if (SpaceEntity.getPosition().y > this->position.y) yPullforce = -pullforce;

  SpaceEntity.addXVelocity(xPullforce);
  SpaceEntity.addYVelocity(yPullforce);
}

float Planet::distanceFrom(SpaceEntity SpaceEntity) {
  return sqrtf(
    powf(SpaceEntity.getPosition().x - this->position.x, 2) +
    powf(SpaceEntity.getPosition().y - this->position.y, 2)
  );
}

bool Planet::isInField(SpaceEntity SpaceEntity) {
  float distFrom = this->distanceFrom(SpaceEntity);
  return distFrom < this->gravitationalFieldSize(); 
}

/**
 * All of this calculation is super approximate and bad because it doesn't matter
 */
float Planet::pullForce(SpaceEntity SpaceEntity) {
  // formula: F = G * (m1 * m2) / r2
  float approxSize = sqrtf(SpaceEntity.getSize().x + SpaceEntity.getSize().y);
  float distBetween = this->distanceFrom(SpaceEntity);

  return 0.001 * ((approxSize * this->size.x) / distBetween);
}