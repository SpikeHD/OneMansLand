#ifndef SPC_PLAYER_H
#define SPC_PLAYER_H

#include "./Entity.h"

using namespace std;

class Player : public Entity {
  public:
    Vector2 size;

    Player(Vector2, Vector2);
    void update();
};

#endif