#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

#include "./Entity.h"
#include "../SpaceWorld.h"

using namespace std;

class Player : public Entity {
  public:
    Player(Vector2, Vector2);
    void update(SpaceWorld);
};

#endif