#include <string>

#include "../Vector.h"
#include "./entity/Entity.h"

using namespace std;

#ifndef SPC_PLANET_H
#define SPC_PLANET_H

class Planet {
  public:
    string name;
    Vector2 position;
    int seed;
    float size;

    Planet(Vector2, float, string);

    void generate();

    int gravitationalFieldSize();
    float distanceFrom(Entity);
    bool isInField(Entity);
    float pullForce(Entity);
};

#endif