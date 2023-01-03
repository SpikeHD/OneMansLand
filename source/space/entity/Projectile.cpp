#include "Projectile.h"

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