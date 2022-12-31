#include <stdio.h>
#include <iostream>
// For screen size constants
#include <gl2d.h>
#include <nds.h>
#include <algorithm>

#include "../../controls.h"
#include "SpacePlayer.h"
#include "../Renderer.h"
#include "../../consts.h"

SpacePlayer::SpacePlayer(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
}

void SpacePlayer::control(SpaceWorld &world) {
  // Offset the velocity accumulation by the zoom level, so we don't move gain lightspeed while zoomed in
  float vel = 0.02 / world.zoomLevel;

  cout << "Keys pressed: ";

  if (btn_up()) {
    this->addYVelocity(-vel);
    cout << "^ ";
  }

  if (btn_down()) {
    this->addYVelocity(vel);
    cout << "v ";
  }

  if (btn_right()) {
    this->addXVelocity(vel);
    cout << "> ";
  }

  if (btn_left()) {
    this->addXVelocity(-vel);
    cout << "< ";
  }

  // Zooming in and out
  if (btn_rbump()) {
    world.zoomLevel = std::clamp(world.zoomLevel + 0.05f, 1.0f, ZOOM_MAX);
    cout << "RB ";
  }

  // Zooming in and out
  if (btn_lbump()) {
    world.zoomLevel = std::clamp(world.zoomLevel - 0.05f, 1.0f, ZOOM_MAX);
    cout << "LB ";
  }

  cout << endl;
}

bool SpacePlayer::collidingWithPlanet(SpaceWorld world, Planet planet) {
  PlanetPosition plPos = planetScreenPosition(world, planet, *this);

  int SCR_X_HALF = SCREEN_WIDTH / 2;
  int SCR_Y_HALF = SCREEN_HEIGHT / 2;

  return plPos.xMin < SCR_X_HALF && plPos.yMin < SCR_Y_HALF &&
         plPos.xMax > SCR_X_HALF && plPos.yMax > SCR_Y_HALF;
}

void SpacePlayer::update(SpaceWorld world) {
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

  cout << "SpacePlayer colliding with planet?: " << this->collidingWithPlanet(world, closest) << endl;
  cout << "SpacePlayer X pos: " << this->position.x << endl;;
  cout << "SpacePlayer y pos: " << this->position.y << endl;
  cout << "SpacePlayer X velocity: " << this->velocity.x << endl;
  cout << "SpacePlayer y velocity: " << this->velocity.y << endl << endl;;

  cout << "Zoom level: " << world.zoomLevel << endl;

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}