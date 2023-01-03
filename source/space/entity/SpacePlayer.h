#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

#include <vector>

#include "Entity.h"
#include "Projectile.h"
#include "Planet.h"

using namespace std;

class SpaceWorld;

class SpacePlayer : public Entity {
  public:
    int health = 50;

    SpacePlayer(Vector2, Vector2);

    bool collidingWithPlanet(SpaceWorld, Planet);
    void control(SpaceWorld &);
    void update(SpaceWorld &);
    int shoot(SpaceWorld&, float);
};

#endif