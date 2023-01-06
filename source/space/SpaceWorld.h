#ifndef SPC_WORLD_H
#define SPC_WORLD_H

#include "entity/Projectile.h"
#include "entity/Planet.h"
#include "entity/Ship.h"
#include "entity/SpacePlayer.h"
#include <vector>

class SpaceWorld {
  public:
    float zoomLevel;
    bool landedOnPlanet;
    int maxProjectiles = 50;

    std::vector<Planet> planets;
    std::vector<Ship> ships;
    std::vector<Projectile> projectiles;

    SpaceWorld();

    void generate();
    void update(SpacePlayer&);

    void spawnShip(Ship);
    void spawnProjectile(Projectile);
};

#endif