#include "Projectile.h"
#include "../SpaceWorld.h"
#include "SpacePlayer.h"

#include <iostream>

// Projectiles based on type
Projectile::Projectile(ProjectileType type) {
  this->lifeStart = time(NULL);

  switch(type) {
    case PROJECTILE_GATTLING:
      this->damage = 2;
      this->speed = 2.0f;
      this->name = "Gattling";
      this->cooldownFrames = 15;
      this->color = RGB15(255,255,0);
      this->setSize(Vector2 {
        2.0f, 2.0f
      });
      break;
  }
}

Projectile::Projectile(int damage, float speed, int cooldownFrames, string name, int color) {
  this->damage = damage;
  this->speed = speed;
  this->name = name;
  this->cooldownFrames = cooldownFrames;
  this->color = color;

  this->lifeStart = time(NULL);
}

void Projectile::update() {
  this->setXPosition(this->getPosition().x + this->getVelocity().x);
  this->setYPosition(this->getPosition().y + this->getVelocity().y);
}

bool Projectile::hittingEntity(SpaceWorld &world, SpacePlayer &player) {
  bool hitting = false;

  // Loop through entities to see if any are being hit
  for (Ship &ship : world.ships) {
    if (this->belongsToPlayer && hitDetect(ship)) {
      ship.removeHealth(world, this->damage);
      hitting = true;

      // Only letting it hit the first thing it hits, rather than multiple things at once
      break;
    }
  }

  // Check if hitting the player
  if (!this->belongsToPlayer && hitDetect(player)) {
    player.removeHealth(this->damage);
    hitting = true;
  }

  return hitting;
}

bool Projectile::hitDetect(Entity &entity) {
  return this->getPosition().x > entity.getPosition().x - entity.getHitSize().x &&
    this->getPosition().x < entity.getPosition().x + entity.getSize().x + entity.getHitSize().x &&
    this->getPosition().y > entity.getPosition().y - entity.getHitSize().y &&
    this->getPosition().y < entity.getPosition().y + entity.getSize().y + entity.getHitSize().y;
}