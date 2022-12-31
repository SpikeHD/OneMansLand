#ifndef SPC_ENTITY_H
#define SPC_ENTITY_H

#include "./../../Vector.h"

using namespace std;

class Entity {
  public:
    Vector2 position;
    Vector2 velocity;

    virtual void update() {};

    void setXVelocity(float);
    void setYVelocity(float);

    void setXPosition(float);
    void setYPosition(float);
};

#endif