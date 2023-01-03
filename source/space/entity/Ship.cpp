#include <stdio.h>
#include <iostream>
#include <math.h>
// For screen size constants
#include <gl2d.h>
#include <algorithm>

#include "Ship.h"
#include "SpacePlayer.h"
#include "../SpaceWorld.h"
#include "../../controls.h"
#include "../Renderer.h"
#include "../../consts.h"

// TODO < 0.2 velocity should be a crash, less is a landing

Ship::Ship(Vector2 position, Vector2 size, bool agressive, int health) {
  this->position = position;
  this->size = size;
  this->agressive = agressive;

  this->maxVelocity = 3;
  this->color = RGB15(255,0,0);
  this->health = health;

  this->hitSize = {
    this->size.x,
    this->size.y,
  };

  this->projectileType = PROJECTILE_GATTLING;
}

Ship::Ship(Vector2 position, Vector2 size) : Ship(position, size, false, 50) {};

void Ship::update(SpaceWorld &world, SpacePlayer &player) {
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

  // Check position relative to player, if they are too close, they are detected, otherwise if they are too far, no longer detected
  if (this->playerInRange(this->radarRange, player.position)) {
    // Player is seen
    this->seesPlayer = true;
  }

  if (!this->playerInRange(this->blindnessDistance, player.position)) {
    // Player got away
    this->seesPlayer = false;
  }

  cout << "Ship sees player?: " << this->seesPlayer << endl;
  cout << "Ship distfromplayer x: " << distFromPlayer.x << endl;
  cout << "Ship distfromplayer y: " << distFromPlayer.y << endl;
  cout << "Ship health: " << this->health << endl;

  if (this->seesPlayer) {
    Vector2 vel = {
      distFromPlayer.x < 0 ? thrust : -thrust,
      distFromPlayer.y < 0 ? thrust : -thrust 
    };

    // Set new velocity
    this->addVelocity(vel);

    // Shoot at players angle
    cout << "Shooting at: ";
    this->shootAt(world, player);
  }

  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

bool Ship::playerInRange(float range, Vector2 playerPos) {
  float dx = playerPos.x - this->position.x;
  float dy = playerPos.y - this->position.y;
  return dx * dx + dy * dy < range * range;
}

Vector2 Ship::distanceFromPlayer(SpacePlayer &player) {
  return Vector2 {
    this->position.x - player.position.x,
    this->position.y - player.position.y
  };
}

void Ship::shoot(SpaceWorld &world, float angle) {
  if (frame < this->canShootAgainFrame) return;

  // Create projectile entity from the base provided projectile
  Projectile p = Projectile(this->projectileType);

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

  p.belongsToPlayer = false;

  world.spawnProjectile(p);

  this->canShootAgainFrame = frame + p.cooldownFrames;
}

void Ship::shootAt(SpaceWorld &world, Entity entity) {
  float angle = std::atan2(entity.position.x - this->position.x, entity.position.y - this->position.y);

  cout << angle << endl;

  this->shoot(world, angle);
}