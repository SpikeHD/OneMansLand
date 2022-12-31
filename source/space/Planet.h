#include <string>

#include "../Vector.h"
#include "./entity/Entity.h"

using namespace std;

#ifndef SPC_PLANET_H
#define SPC_PLANET_H

class Planet : public Entity {
  public:
    string name;
    int seed;

    Planet(Vector2, float, string);

    void generate();

    int gravitationalFieldSize();
    void pull(Entity &);
    float distanceFrom(Entity);
    bool isInField(Entity);
    float pullForce(Entity);
};

#endif