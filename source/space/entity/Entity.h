#ifndef SPC_ENTITY_H
#define SPC_ENTITY_H

#include <string>
#include "./../../Vector.h"

using namespace std;

class Entity {
  public:
    int health;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    // Hitbox type thingy
    Vector2 hitSize;
    int color;
    float maxVelocity = 2;

    string name;

    virtual void update() {};

    void setXVelocity(float);
    void setYVelocity(float);
    void setVelocity(Vector2);
    void addXVelocity(float);
    void addYVelocity(float);
    void addVelocity(Vector2);

    void setXPosition(float);
    void setYPosition(float);
    void setPosition(Vector2);
};

#endif