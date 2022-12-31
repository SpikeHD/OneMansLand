#include <stdio.h>
#include <iostream>
// For screen size constants
#include <gl2d.h>

#include "Player.h"
#include "../Renderer.h"

Player::Player(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
}

bool Player::collidingWithPlanet(SpaceWorld world, Planet planet) {
  PlanetPosition plPos = planetScreenPosition(world, planet, *this);

  int SCR_X_HALF = SCREEN_WIDTH / 2;
  int SCR_Y_HALF = SCREEN_HEIGHT / 2;

  return plPos.xMin < SCR_X_HALF && plPos.yMin < SCR_Y_HALF &&
         plPos.xMax > SCR_X_HALF && plPos.yMax > SCR_Y_HALF;
} 

void Player::update(SpaceWorld world) {
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
  cout << "Planet size: " << closest.size.x << endl;
  cout << "Planet pull force: " << pullforce << endl << endl;

  cout << "Player colliding with planet?: " << this->collidingWithPlanet(world, closest) << endl;
  cout << "Player X pos: " << this->position.x << endl;;
  cout << "Player y pos: " << this->position.y << endl;
  cout << "Player X velocity: " << this->velocity.x << endl;
  cout << "Player y velocity: " << this->velocity.y << endl << endl;;

  cout << "Zoom level: " << world.zoomLevel << endl;

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}