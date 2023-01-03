#include "Projectile.h"

#include <iostream>

Projectile::Projectile() {
  this->damage = 2;
  this->speed = 0.01f;
  this->name = "Gattling Gun";
  this->cooldownSec = 1;

  this->lifeStart = time(NULL);
}

Projectile::Projectile(int damage, float speed, int cooldownSec, string name, int color) {
  this->damage = damage;
  this->speed = speed;
  this->name = name;
  this->cooldownSec = cooldownSec;

  this->lifeStart = time(NULL);
}

Projectile::Projectile(const Projectile& proj) {
  this->damage = proj.damage;
  this->speed = proj.speed;
  this->name = proj.name;
  this->cooldownSec = proj.cooldownSec;
  this->color = proj.color;

  this->lifeStart = time(NULL);
}

void Projectile::update() {
  // this->setXPosition(this->position.x + this->velocity.x);
  // this->setYPosition(this->position.y + this->velocity.y);
}