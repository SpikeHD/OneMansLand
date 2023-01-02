#include <string>

#include "../../Vector.h"
#include "Entity.h"

using namespace std;

#ifndef SPC_PLANET_H
#define SPC_PLANET_H

class Planet : public Entity {
  public:
    int seed;
    int color;

    Planet(Vector2, float, string, int);

    void generate();
    void update() {};

    int gravitationalFieldSize();
    void pull(Entity &);
    float distanceFrom(Entity);
    bool isInField(Entity);
    float pullForce(Entity);
};

#endif