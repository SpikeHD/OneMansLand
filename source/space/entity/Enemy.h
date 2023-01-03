#include <vector>

#include "Entity.h"
#include "Projectile.h"
#include "SpacePlayer.h"
#include "../SpaceWorld.h"

#ifndef SPC_ENEMY_H
#define SPC_ENEMY_H

class Enemy : public Entity {
  public:
    float maxProjectiles = 1;
    Projectile proj;
    std::vector<Projectile> projectiles;

    Enemy(Vector2, Vector2);

    void update(SpacePlayer&);
    void shoot(int);
};

#endif