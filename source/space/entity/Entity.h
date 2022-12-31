#ifndef SPC_ENTITY_H
#define SPC_ENTITY_H

#include "./../../Vector.h"

using namespace std;

class Entity {
  public:
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    float maxVelocity = 2;

    virtual void update() {};

    void setXVelocity(float);
    void setYVelocity(float);
    void addXVelocity(float);
    void addYVelocity(float);
    void addVelocity(Vector2);

    void setXPosition(float);
    void setYPosition(float);
};

#endif