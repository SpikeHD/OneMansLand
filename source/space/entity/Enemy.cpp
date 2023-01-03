#include <stdio.h>
#include <iostream>
#include <math.h>
// For screen size constants
#include <gl2d.h>
#include <algorithm>

#include "Enemy.h"
#include "SpacePlayer.h"
#include "../../controls.h"
#include "../Renderer.h"
#include "../../consts.h"

// TODO < 0.2 velocity should be a crash, less is a landing

Enemy::Enemy(Vector2 position, Vector2 size) {
  this->position = position;
  this->size = size;

  this->maxVelocity = 3;
  this->color = RGB15(255,0,0);
}

void Enemy::update(SpacePlayer &player) {
  Vector2 distFromPlayer = distanceFromPlayer(player);
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

  // Check position relative to player, if they are too close, they are detected, otherwise if they are too far, no longer detected
  if (this->playerInRange(this->radarRange, player.position)) {
    // Player is seen
    this->seesPlayer = true;
  }

  if (!this->playerInRange(this->blindnessDistance, player.position)) {
    // Player got away
    this->seesPlayer = false;
  }

  cout << "Enemy sees player?: " << this->seesPlayer << endl;
  cout << "Enemy distfromplayer x: " << distFromPlayer.x << endl;
  cout << "Enemy distfromplayer y: " << distFromPlayer.y << endl;

  if (this->seesPlayer) {
    Vector2 vel = {
      distFromPlayer.x < 0 ? thrust : -thrust,
      distFromPlayer.y < 0 ? thrust : -thrust 
    };

    // Set new velocity
    this->addVelocity(vel);
  }

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

bool Enemy::playerInRange(float range, Vector2 playerPos) {
  float dx = playerPos.x - this->position.x;
  float dy = playerPos.y - this->position.y;
  return dx * dx + dy * dy < range * range;
}

Vector2 Enemy::distanceFromPlayer(SpacePlayer &player) {
  return Vector2 {
    this->position.x - player.position.x,
    this->position.y - player.position.y
  };
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