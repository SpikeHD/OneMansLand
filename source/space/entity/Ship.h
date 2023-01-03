#ifndef SPC_ENEMY_H
#define SPC_ENEMY_H

#include <vector>

#include "Entity.h"
#include "Projectile.h"

class SpacePlayer;

class Ship : public Entity {
  public:
    float maxProjectiles = 1;
    float thrust = 0.01f;

    bool agressive = false;

    // How far away the player can be seen
    int radarRange = 50;

    // How far the player has to go before they are lost by the enemy
    int blindnessDistance = 70;

    bool seesPlayer;
    Projectile proj;
    std::vector<Projectile> projectiles;

    Ship(Vector2, Vector2);
    Ship(Vector2, Vector2, bool);

    bool playerInRange(float, Vector2);
    Vector2 distanceFromPlayer(SpacePlayer&);
    void update(SpacePlayer&);
    void shoot(int);
};

#endif