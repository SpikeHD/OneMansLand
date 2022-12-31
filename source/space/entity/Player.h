#include "Entity.h"
#include "../SpaceWorld.h"

#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

using namespace std;

class Player : public Entity {
  public:
    Player(Vector2, Vector2);

    bool collidingWithPlanet(SpaceWorld, Planet);

    void update(SpaceWorld);
};

#endif