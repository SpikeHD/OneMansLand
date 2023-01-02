#include <stdio.h>
#include <iostream>
#include <math.h>
// For screen size constants
#include <gl2d.h>
#include <nds.h>
#include <algorithm>

#include "../../controls.h"
#include "SpacePlayer.h"
#include "../Renderer.h"
#include "../../consts.h"

// TODO < 0.2 velocity should be a acrash, less is a landing

SpacePlayer::SpacePlayer(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
  this->color = RGB15(255,255,255);
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
  EntityScreenPos plPos = entityScreenPosition(world, planet, *this);

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

  // Projectile handling
  for (Projectile &proj : this->projectiles) {
    if (this->maxProjectiles < this->projectiles.size()) {
      this->projectiles.erase(this->projectiles.begin());
    }

    cout << "update pvely" << proj.velocity.y << endl; 
    cout << "update pposy" << proj.position.y << endl; 

    proj.update();
  }

  cout << "Closest planet:" << closest.name << endl;
  cout << "Dist from planet: " << distFrom << endl;
  cout << "Planet X: " << closest.position.x << endl;
  cout << "Planet Y: " << closest.position.y << endl;
  cout << "Planet size: " << closest.size.x << endl;

  cout << "Colliding with planet?: " << this->collidingWithPlanet(world, closest) << endl;
  cout << "Player X pos: " << this->position.x << endl;
  cout << "Player y pos: " << this->position.y << endl;
  cout << "Player X velocity: " << this->velocity.x << endl;
  cout << "Player y velocity: " << this->velocity.y << endl << endl;

  cout << "Zoom level: " << world.zoomLevel << endl;

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

void SpacePlayer::shoot(int angle) {
  // Create projectile entity from the base provided projectile
  Projectile newProj(this->proj);

  Vector2 vel = {
    cosf(angle) * newProj.speed,
    sinf(angle) * newProj.speed
  };

  Vector2 pos = {
    this->position.x,
    this->position.y
  };

  newProj.setVelocity(vel);
  newProj.setPosition(pos);

  //cout << "proj vel y: " << newProj.velocity.y << endl;
  //cout << "newproj pos x: " << newProj.position.x << endl;

  // this->projectiles.push_back(newProj);
}