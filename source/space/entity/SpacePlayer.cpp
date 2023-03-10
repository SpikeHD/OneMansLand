#include <stdio.h>
#include <iostream>
#include <math.h>
// For screen size constants
#include <gl2d.h>
#include <nds.h>
#include <algorithm>

#include "SpacePlayer.h"
#include "../SpaceWorld.h"
#include "../../controls.h"
#include "../SpaceRenderer.h"
#include "../../consts.h"

// TODO < 0.2 velocity should be a acrash, less is a landing

SpacePlayer::SpacePlayer(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;
  this->hitSize = size;

  this->maxVelocity = 3;
  this->color = RGB15(255,255,255);
  this->projectileType = PROJECTILE_GATTLING;
}

void SpacePlayer::control(SpaceWorld &world) {
  // Offset the velocity accumulation by the zoom level, so we don't move gain lightspeed while zoomed in
  float vel = 0.02 / world.zoomLevel;

  cout << "Keys pressed: ";

  if (btn_up()) {
    this->addYVelocity(-vel);
    
    if (this->velocity.y > 0) {
      // We are braking, double the velocity applied
      this->addYVelocity(-vel);
    }

    cout << "^ ";
  }

  if (btn_down()) {
    this->addYVelocity(vel);

    if (this->velocity.y < 0) {
      // We are braking, double the velocity applied
      this->addYVelocity(vel);
    }

    cout << "v ";
  }

  if (btn_right()) {
    this->addXVelocity(vel);

    if (this->velocity.x < 0) {
      // We are braking, double the velocity applied
      this->addXVelocity(vel);
    }

    cout << "> ";
  }

  if (btn_left()) {
    this->addXVelocity(-vel);

    if (this->velocity.x > 0) {
      // We are braking, double the velocity applied
      this->addXVelocity(-vel);
    }

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
  SpaceEntityScreenPos plPos = SpaceEntityScreenPosition(world, planet, *this);

  int SCR_X_HALF = SCREEN_WIDTH / 2;
  int SCR_Y_HALF = SCREEN_HEIGHT / 2;

  return plPos.xMin < SCR_X_HALF && plPos.yMin < SCR_Y_HALF &&
         plPos.xMax > SCR_X_HALF && plPos.yMax > SCR_Y_HALF;
}

void SpacePlayer::update(SpaceWorld &world) {
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

  cout << "Closest planet:" << closest.name << endl;
  cout << "Dist from planet: " << distFrom << endl;
  cout << "Planet X: " << closest.getPosition().x << endl;
  cout << "Planet Y: " << closest.getPosition().y << endl;

  cout << "Colliding with planet?: " << this->collidingWithPlanet(world, closest) << endl;
  cout << "Player X pos: " << this->position.x << endl;
  cout << "Player y pos: " << this->position.y << endl << endl;

  cout << "Zoom level: " << world.zoomLevel << endl;

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

int SpacePlayer::shoot(SpaceWorld &world, float angle) {
  // Create projectile SpaceEntity from the base provided projectile
  Projectile p = Projectile(PROJECTILE_GATTLING);

  Vector2 vel = {
    (sinf(angle) * p.speed) + this->velocity.x,
    (cosf(angle) * p.speed) + this->velocity.y
  };

  Vector2 pos = {
    this->position.x,
    this->position.y
  };

  p.setVelocity(vel);
  p.setPosition(pos);

  p.fromSquad = 0;
  p.fromShip = 0;

  world.spawnProjectile(p);

  return p.cooldownFrames;
}

void SpacePlayer::removeHealth(int h) {
  this->health = this->health - h;
}

void SpacePlayer::addHealth(int h) {
  this->health = this->health + h;
}