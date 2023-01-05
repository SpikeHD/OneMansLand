#include "Squad.h"
#include "Ship.h"
#include "../../consts.h"

void spawnSquad(SpaceWorld &world, int shipCount, bool enemy, Vector2 position) {
  // Spawn each ship near eachother, around the position spocified
  for (int i = 0; i < shipCount; i++) {
    float size = (rand() % (int)SHIP_MAX_SIZE - 4.0f) + 4.0f;
    int health = size * 10; 
    Vector2 spos = {
      position.x + (rand() % 60 + (- 30)),
      position.y + (rand() % 60 + (- 30))
    };
    Vector2 ssize = {
      size, size
    };

    Ship s = Ship(spos, ssize, enemy, health);

    world.spawnShip(s);
  }
}

void spawnBattle(SpaceWorld &world, int enemyCount, int allyCount) {}