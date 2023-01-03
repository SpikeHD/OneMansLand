#include "Entity.h"
#include "../Renderer.h"
#include <algorithm>

void Entity::setXVelocity(float vel) {
  this->velocity.x = vel;
}

void Entity::setYVelocity(float vel) {
  this->velocity.y = vel;
}

void Entity::setVelocity(Vector2 vel) {
  this->velocity = vel;
}

void Entity::addXVelocity(float vel) {
  this->velocity.x += std::clamp(vel, -maxVelocity, maxVelocity);
}

void Entity::addYVelocity(float vel) {
  this->velocity.y += std::clamp(vel, -maxVelocity, maxVelocity);
}

void Entity::addVelocity(Vector2 vel) {
  this->addXVelocity(vel.x);
  this->addYVelocity(vel.y);
}

void Entity::setXPosition(float pos) {
  this->position.x = pos;
}

void Entity::setYPosition(float pos) {
  this->position.y = pos;
}

void Entity::setPosition(Vector2 pos) {
  this->position = pos;
}