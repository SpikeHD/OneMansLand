#include "Entity.h"
#include "../SpaceWorld.h"

#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

using namespace std;

class SpacePlayer : public Entity {
  public:
    SpacePlayer(Vector2, Vector2);

    bool collidingWithPlanet(SpaceWorld, Planet);

    void control(SpaceWorld &);
    void update(SpaceWorld);
};

#endif