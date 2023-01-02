#include <gl2d.h>
#include <ctime>
#include <string>

#include "Entity.h"

#ifndef SPC_PROJECTILE_H
#define SPC_PROJECTILE_H

class Projectile : public Entity {
  public:
    int damage;
    float speed;
    int cooldownSec;
    int color;

    time_t lifeStart;

    // TODO Smol square until we turn into sprite
    Vector2 size {
      2, 2
    };

    Projectile();
    Projectile(const Projectile&);
    Projectile(int, float, int, string, int);

    void update();
};

#endif