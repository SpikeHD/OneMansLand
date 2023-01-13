#include "SpaceEntity.h"
#include <algorithm>

void SpaceEntity::setXVelocity(float vel) {
  this->velocity.x = vel;
}

void SpaceEntity::setYVelocity(float vel) {
  this->velocity.y = vel;
}

void SpaceEntity::setVelocity(Vector2 vel) {
  this->velocity = vel;
}

void SpaceEntity::addXVelocity(float vel) {
  this->velocity.x += std::clamp(vel, -maxVelocity, maxVelocity);
}

void SpaceEntity::addYVelocity(float vel) {
  this->velocity.y += std::clamp(vel, -maxVelocity, maxVelocity);
}

void SpaceEntity::addVelocity(Vector2 vel) {
  this->addXVelocity(vel.x);
  this->addYVelocity(vel.y);
}

void SpaceEntity::setXPosition(float pos) {
  this->position.x = pos;
}

void SpaceEntity::setYPosition(float pos) {
  this->position.y = pos;
}

void SpaceEntity::setPosition(Vector2 pos) {
  this->position = pos;
}

void SpaceEntity::setSize(Vector2 size) {
  this->size = size;
}

void SpaceEntity::setHitSize(Vector2 hitSize) {
  this->hitSize = hitSize;
}

Vector2 SpaceEntity::getVelocity() {
  return this->velocity;
}

Vector2 SpaceEntity::getPosition() {
  return this->position;
}

Vector2 SpaceEntity::getSize() {
  return this->size;
}

Vector2 SpaceEntity::getHitSize() {
  return this->hitSize;
}