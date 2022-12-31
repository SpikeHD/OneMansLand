#include "./Entity.h"

void Entity::setXVelocity(float vel) {
  this->velocity.x = vel;
}

void Entity::setYVelocity(float vel) {
  this->velocity.y = vel;
}

void Entity::setXPosition(float pos) {
  this->position.x = pos;
}

void Entity::setYPosition(float pos) {
  this->position.y = pos;
}