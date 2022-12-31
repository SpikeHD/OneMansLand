#include "./Player.h"

Player::Player(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
}

void Player::update() {
  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}