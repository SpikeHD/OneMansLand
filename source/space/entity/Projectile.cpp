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
      this->speed = 1.0f;
      this->name = "Gattling";
      this->cooldownFrames = 10;
      this->color = RGB15(255,255,0);
      this->size = Vector2 {
        2.0f, 2.0f
      };
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
  this->setXPosition(this->position.x + this->velocity.x);
  this->setYPosition(this->position.y + this->velocity.y);
}

bool Projectile::hittingEntity(SpaceWorld &world, SpacePlayer &player) {
  bool hitting = false;

  // Loop through entities to see if any are being hit
  for (Entity &entity : world.ships) {
    if (hitDetect(entity)) {
      entity.health -= damage;
      hitting = true;

      // Only letting it hit the first thing it hits, rather than multiple thigns at once
      break;
    }
  }

  // Check if hitting the player
  if (!this->belongsToPlayer && hitDetect(player)) {
    player.health -= this->damage;
    hitting = true;
  }

  return hitting;
}

bool Projectile::hitDetect(Entity &entity) {
  return this->position.x > entity.position.x - entity.hitSize.x &&
    this->position.x < entity.position.x + entity.size.x + entity.hitSize.x &&
    this->position.y > entity.position.y - entity.hitSize.y &&
    this->position.y < entity.position.y + entity.size.y + entity.hitSize.y;
}