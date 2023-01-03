#include <stdio.h>
#include <iostream>
#include <math.h>
// For screen size constants
#include <gl2d.h>
#include <algorithm>

#include "Enemy.h"
#include "../../controls.h"
#include "../Renderer.h"
#include "../../consts.h"

// TODO < 0.2 velocity should be a crash, less is a landing

Enemy::Enemy(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
  this->color = RGB15(255,255,255);
}

void Enemy::update(SpacePlayer &player) {
  //Planet closest = world.planets.at(0);

  // for (Planet p : world.planets) {
  //   if (p.distanceFrom(*this) < closest.distanceFrom(*this)) {
  //     closest = p;
  //   }

  //   if (p.isInField(*this)) {
  //     p.pull(*this);
  //   }
  // }

  // Projectile handling
  for (Projectile &proj : this->projectiles) {
    if (this->maxProjectiles < this->projectiles.size()) {
      this->projectiles.erase(this->projectiles.begin());
    }

    cout << "update evely" << proj.velocity.y << endl; 
    cout << "update eposy" << proj.position.y << endl; 

    proj.update();
  }

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

void Enemy::shoot(int angle) {
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