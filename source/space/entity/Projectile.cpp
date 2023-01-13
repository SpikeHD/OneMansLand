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

bool Projectile::hittingSpaceEntity(SpaceWorld &world, SpacePlayer &player) {
  bool hitting = false;

  // Loop through entities to see if any are being hit
  for (Ship &ship : world.ships) {
    if ((this->fromSquad != ship.squadId || (this->fromSquad == -1 && this->fromShip != ship.id)) && hitDetect(ship)) {
      ship.removeHealth(world, this->damage);
      hitting = true;

      // Only letting it hit the first thing it hits, rather than multiple things at once
      break;
    }
  }

  // Check if hitting the player
  if (!this->fromSquad == 0 && hitDetect(player)) {
    player.removeHealth(this->damage);
    hitting = true;
  }

  return hitting;
}

bool Projectile::hitDetect(SpaceEntity &SpaceEntity) {
  return this->getPosition().x > SpaceEntity.getPosition().x - SpaceEntity.getHitSize().x &&
    this->getPosition().x < SpaceEntity.getPosition().x + SpaceEntity.getSize().x + SpaceEntity.getHitSize().x &&
    this->getPosition().y > SpaceEntity.getPosition().y - SpaceEntity.getHitSize().y &&
    this->getPosition().y < SpaceEntity.getPosition().y + SpaceEntity.getSize().y + SpaceEntity.getHitSize().y;
}