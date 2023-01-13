#ifndef SPC_ENEMY_H
#define SPC_ENEMY_H

#include <vector>

#include "SpaceEntity.h"
#include "Projectile.h"

extern int frame;

class SpacePlayer;
class SpaceWorld;

class Ship : public SpaceEntity {
  public:
    bool disabled = false;
    int id = -1;
    int squadId = -1;
    int canShootAgainFrame = 0;
    ProjectileType projectileType;
    float maxProjectiles = 1;
    float thrust = 0.01f;

    bool agressive = false;

    // How far away the player can be seen
    int radarRange = 50;

    // How far the player has to go before they are lost by the enemy
    int blindnessDistance = 140;

    bool seesPlayer;

    Ship(Vector2, Vector2);
    Ship(Vector2, Vector2, bool, int);

    bool playerInRange(float, Vector2);
    Vector2 signedDistance(SpaceEntity&);
    void update(SpaceWorld&, SpacePlayer&);
    void moveTo(SpaceEntity&);
    void shoot(SpaceWorld&, float);
    void shootAt(SpaceWorld&, SpaceEntity);

    void removeHealth(SpaceWorld&, int);
    void addHealth(int);

  private:
    int health = 50;
};

#endif