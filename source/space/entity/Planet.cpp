#include <cmath>

#include "Planet.h"
#include "Entity.h"

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

void Planet::pull(Entity &entity) {
  bool inField = this->isInField(entity);
  float pullforce = this->pullForce(entity);

  if (!inField) pullforce = 0;

  float xPullforce = pullforce;
  float yPullforce = pullforce;

  if (entity.position.x > this->position.x) xPullforce = -pullforce;
  if (entity.position.y > this->position.y) yPullforce = -pullforce;

  entity.addXVelocity(xPullforce);
  entity.addYVelocity(yPullforce);
}

float Planet::distanceFrom(Entity entity) {
  return sqrtf(
    powf(entity.position.x - this->position.x, 2) +
    powf(entity.position.y - this->position.y, 2)
  );
}

bool Planet::isInField(Entity entity) {
  float distFrom = this->distanceFrom(entity);
  return distFrom < this->gravitationalFieldSize(); 
}

/**
 * All of this calculation is super approximate and bad because it doesn't matter
 */
float Planet::pullForce(Entity entity) {
  // formula: F = G * (m1 * m2) / r2
  float approxSize = sqrtf(entity.size.x + entity.size.y);
  Vector2 centerOfEntity = {
    entity.position.x + (approxSize / 2),
    entity.position.y + (approxSize / 2)
  };
  float distBetween = this->distanceFrom(entity);

  return 0.001 * ((approxSize * this->size.x) / distBetween);
}