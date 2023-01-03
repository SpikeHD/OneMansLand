#ifndef SPC_PROJECTILE_H
#define SPC_PROJECTILE_H

#include <gl2d.h>
#include <ctime>
#include <string>

#include "Entity.h"

enum ProjectileType {
  PROJECTILE_GATTLING,
  PROJECTILE_MISSLE
};

class Projectile : public Entity {
  public:
    int damage;
    float speed;
    int cooldownFrames;
    int color;

    time_t lifeStart;

    Projectile(int, float, int, string, int);
    Projectile(ProjectileType);

    void update();
};

#endif