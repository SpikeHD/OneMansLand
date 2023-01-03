#ifndef SPC_WORLD_H
#define SPC_WORLD_H

#include "entity/Projectile.h"
#include "entity/Planet.h"
#include "entity/Enemy.h"
#include "entity/SpacePlayer.h"
#include <vector>

class SpaceWorld {
  public:
    float zoomLevel;
    bool landedOnPlanet;

    std::vector<Planet> planets;
    std::vector<Enemy> enemies;

    SpaceWorld();

    void generate();
    void update(SpacePlayer&);

    void spawnEnemy(Enemy);
};

#endif