#ifndef SPC_PLANET_H
#define SPC_PLANET_H

#include <string>

#include "../../Vector.h"
#include "SpaceEntity.h"

using namespace std;
class Planet : public SpaceEntity {
  public:
    int seed;
    int color;

    Planet(Vector2, float, string, int);

    void generate();
    void update() {};

    int gravitationalFieldSize();
    void pull(SpaceEntity &);
    float distanceFrom(SpaceEntity);
    bool isInField(SpaceEntity);
    float pullForce(SpaceEntity);
};

#endif