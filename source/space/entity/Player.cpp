#include "./Player.h"
#include <stdio.h>

Player::Player(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
}

void Player::update(SpaceWorld world) {
  // TODO find closeby planets and calc that way
  Planet p = world.planets.at(0);
  bool inField = p.isInField(*this);
  float distFrom = p.distanceFrom(*this);
  float pullforce = p.pullForce(*this);

  if (!inField) pullforce = 0;

  float xPullforce = pullforce;
  float yPullforce = pullforce;

  if (this->position.x > p.position.x) xPullforce = -pullforce;
  if (this->position.y > p.position.y) yPullforce = -pullforce;

  printf("Is in field?: %d\n", inField);
  printf("Dist from planet: %.5f\n", distFrom);
  printf("X Pullforce: %.5f\n", xPullforce);
  printf("Y Pullforce: %.5f\n", yPullforce);

  printf("Player X velocity: %.4f\n", this->velocity.x);
  printf("Player y velocity: %.4f\n", this->velocity.y);

  this->setXVelocity(this->velocity.x + xPullforce);
  this->setYVelocity(this->velocity.y + yPullforce);

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}