#ifndef SPC_WORLD_H
#define SPC_WORLD_H

#include "SpaceEntity/Projectile.h"
#include "SpaceEntity/Planet.h"
#include "SpaceEntity/Ship.h"
#include "SpaceEntity/SpacePlayer.h"
#include <vector>

class SpaceWorld {
  public:
    float zoomLevel;
    bool landedOnPlanet;
    int maxProjectiles = 10;

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