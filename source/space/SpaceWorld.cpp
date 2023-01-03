#include <string>
#include <nds.h>
#include <gl2d.h>

#include "SpaceWorld.h"
#include "../consts.h"

#include <iostream>

SpaceWorld::SpaceWorld() {
  this->zoomLevel = 1;
  this->landedOnPlanet = false;
}

void SpaceWorld::generate() {
  // TODO make planets dynamically
  int planets = rand() % 6 + 6;

  for (int i = 0; i < planets; i++) {
    Vector2 pos = {
      rand() % 20000 - 10000,
      rand() % 20000 - 10000
    };
    int color = RGB15(rand() % 255, rand() % 255, rand() % 255);

    Planet p = Planet(pos, rand() % 100 + 100, string("Planet") + to_string(i), color);
    this->planets.push_back(p);
  }
}

void SpaceWorld::update(SpacePlayer &player) {
  for (Ship &ship : this->ships) {
    ship.update(player);
  }

    // Projectile handling
  for (Projectile &proj : this->projectiles) {
    if (this->maxProjectiles < this->projectiles.size()) {
      this->projectiles.erase(this->projectiles.begin());
    }

    proj.update();
  }
}

void SpaceWorld::spawnShip(Ship ship) {
  this->ships.push_back(ship);
}

void SpaceWorld::spawnProjectile(Projectile projectile) {
  this->projectiles.push_back(projectile);
}