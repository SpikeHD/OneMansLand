#ifndef SPC_WORLD_H
#define SPC_WORLD_H

#include "entity/Projectile.h"
#include "entity/Planet.h"
#include "entity/Enemy.h"
#include <vector>
#include <deque>


class SpaceWorld {
  public:
    float zoomLevel;
    bool landedOnPlanet;

    std::vector<Planet> planets;
    std::vector<Enemy> enemies;

    SpaceWorld();

    void generate();
    void update();

    void spawnEnemy(Enemy);
};

#endif