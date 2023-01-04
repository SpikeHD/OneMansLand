#ifndef SPC_ENTITY_H
#define SPC_ENTITY_H

#include <string>
#include "./../../Vector.h"

using namespace std;

class Entity {
  public:
    int color;
    float maxVelocity = 2;

    string name;

    virtual void update() {};

    Vector2 getVelocity();
    Vector2 getPosition();
    Vector2 getSize();
    Vector2 getHitSize();

    void setXVelocity(float);
    void setYVelocity(float);
    void setVelocity(Vector2);
    void addXVelocity(float);
    void addYVelocity(float);
    void addVelocity(Vector2);

    void setXPosition(float);
    void setYPosition(float);
    void setPosition(Vector2);

    void setSize(Vector2);
    void setHitSize(Vector2);

  protected:
    int health;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    // Hitbox type thingy
    Vector2 hitSize;
};

#endif