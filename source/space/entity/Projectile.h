#ifndef SPC_PROJECTILE_H
#define SPC_PROJECTILE_H

#include <gl2d.h>
#include <ctime>
#include <string>

#include "SpaceEntity.h"

enum ProjectileType {
  PROJECTILE_GATTLING,
  PROJECTILE_MISSLE
};

class SpaceWorld;
class SpacePlayer;

class Projectile : public SpaceEntity {
  public:
    int damage;
    float speed;
    int cooldownFrames;
    int color;
    // 0 = player
    int fromSquad;
    // 0 = player
    int fromShip;

    time_t lifeStart;

    Projectile(int, float, int, string, int);
    Projectile(ProjectileType);

    void update();
    bool hittingSpaceEntity(SpaceWorld&, SpacePlayer&);
    bool hitDetect(SpaceEntity&);
};

#endif