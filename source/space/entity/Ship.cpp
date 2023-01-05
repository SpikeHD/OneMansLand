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
  this->setPosition(position);
  this->setSize(size);
  this->agressive = agressive;
  this->color = agressive ? RGB15(255, 0, 0) : RGB15(0, 255, 0);

  this->maxVelocity = SHIP_MAX_VELOCITY;
  this->health = health;

  this->setHitSize(Vector2 {
    this->getSize().x,
    this->getSize().y,
  });

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
  if (this->playerInRange(this->radarRange, player.getPosition())) {
    // Player is seen
    this->seesPlayer = true;
  }

  if (!this->playerInRange(this->blindnessDistance, player.getPosition())) {
    // Player got away
    this->seesPlayer = false;
  }

  cout << "Ship sees player?: " << this->seesPlayer << endl;
  cout << "Ship distfromplayer x: " << distFromPlayer.x << endl;
  cout << "Ship distfromplayer y: " << distFromPlayer.y << endl;
  cout << "Ship health: " << this->health << endl;
  cout << "Ship is aggresive?: " << this->agressive << endl;

  if (this->disabled) {
    // Brake until at zero
    if (velocity.x == 0 && velocity.y == 0) {
      // No need to keep reassigning zeros
      return;
    }

    if (velocity.x > 0) {
      this->addXVelocity(-thrust);
    } else {
      this->addXVelocity(thrust);
    }

    if (velocity.y > 0) {
      this->addYVelocity(-thrust);
    } else {
      this->addYVelocity(thrust);
    }

    this->setXPosition(this->getPosition().x + this->getVelocity().x);
    this->setYPosition(this->getPosition().y + this->getVelocity().y);

    return;
  }

  if (this->seesPlayer && this->agressive) {
    Vector2 vel = {
      distFromPlayer.x < 0 ? thrust : -thrust,
      distFromPlayer.y < 0 ? thrust : -thrust 
    };

    // Set new velocity
    this->addVelocity(vel);

    // Shoot at players angle
    this->shootAt(world, player);
  }

  this->setXPosition(this->getPosition().x + this->getVelocity().x);
  this->setYPosition(this->getPosition().y + this->getVelocity().y);
}

bool Ship::playerInRange(float range, Vector2 playerPos) {
  float dx = playerPos.x - this->getPosition().x;
  float dy = playerPos.y - this->getPosition().y;
  return dx * dx + dy * dy < range * range;
}

Vector2 Ship::distanceFromPlayer(SpacePlayer &player) {
  return Vector2 {
    this->getPosition().x - player.getPosition().x,
    this->getPosition().y - player.getPosition().y
  };
}

void Ship::shoot(SpaceWorld &world, float angle) {
  if (frame < this->canShootAgainFrame || this->disabled) return;

  // Create projectile entity from the base provided projectile
  Projectile p = Projectile(this->projectileType);

  Vector2 vel = {
    (sinf(angle) * p.speed) + this->getVelocity().x,
    (cosf(angle) * p.speed) + this->getVelocity().y
  };

  Vector2 pos = {
    this->getPosition().x,
    this->getPosition().y
  };

  p.setVelocity(vel);
  p.setPosition(pos);

  p.belongsToPlayer = false;

  world.spawnProjectile(p);

  this->canShootAgainFrame = frame + p.cooldownFrames;
}

void Ship::shootAt(SpaceWorld &world, Entity entity) {
  float angle = std::atan2(entity.getPosition().x - this->getPosition().x, entity.getPosition().y - this->getPosition().y);

  // Add some random noise to the angle to make it more fair (0.0 to 1.0)
  float noise = -0.3 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(0.6));

  this->shoot(world, angle + noise);
}

void Ship::removeHealth(SpaceWorld& world, int h) {
  this->health = this->health - h;

  // Make agressive if not already
  if (!this->agressive) {
    this->agressive = true;

    // If in a squad, set squad members to aggro as well
    if (this->squadId) {
      for (Ship &s : world.ships) {
        if (s.squadId == this->squadId) {
          s.agressive = true;
        }
      }
    }
  }

  if (health <= 0) {
    this->health = 0;
    this->disabled = true;
  }
}

void Ship::addHealth(int h) {
  this->health = this->health + h;
}