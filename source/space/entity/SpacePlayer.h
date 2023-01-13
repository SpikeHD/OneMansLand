#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

#include <vector>

#include "SpaceEntity.h"
#include "Projectile.h"
#include "Planet.h"

using namespace std;

class SpaceWorld;

class SpacePlayer : public SpaceEntity {
  public:
    ProjectileType projectileType;

    SpacePlayer(Vector2, Vector2);

    bool collidingWithPlanet(SpaceWorld, Planet);
    void control(SpaceWorld &);
    void update(SpaceWorld &);
    int shoot(SpaceWorld&, float);

    void removeHealth(int);
    void addHealth(int);

  private:
    int health = 50;
};

#endif