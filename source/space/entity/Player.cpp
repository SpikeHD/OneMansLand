#include "./Player.h"
#include <stdio.h>
#include <iostream>

Player::Player(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
}

void Player::update(SpaceWorld world) {
  // TODO find closeby planets and calc that way
  Planet closest = world.planets.at(0);

  for (Planet p : world.planets) {
    if (p.distanceFrom(*this) < closest.distanceFrom(*this)) {
      closest = p;
    }

    if (p.isInField(*this)) {
      p.pull(*this);
    }
  }

  bool inField = closest.isInField(*this);
  float distFrom = closest.distanceFrom(*this);
  float pullforce = closest.pullForce(*this);

  cout << "Closest planet:" << closest.name << endl;;
  cout << "Is in field?: " << inField << endl;
  cout << "Dist from planet: " << distFrom << endl;
  cout << "Planet X: " << closest.position.x << endl;
  cout << "Planet Y: " << closest.position.y << endl;
  cout << "Planet pull force: " << pullforce << endl << endl;

  cout << "Player X pos: " << this->position.x << endl;;
  cout << "Player y pos: " << this->position.y << endl;
  cout << "Player X velocity: " << this->velocity.x << endl;
  cout << "Player y velocity: " << this->velocity.y << endl << endl;;

  cout << "Zoom level: " << world.zoomLevel << endl;

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}