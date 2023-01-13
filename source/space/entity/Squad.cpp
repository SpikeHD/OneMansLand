#include "Squad.h"
#include "Ship.h"
#include "../../consts.h"

void spawnSquad(SpaceWorld &world, int shipCount, bool enemy, Vector2 position) {
  Vector2 squadVel = {
    -0.3 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(1.0)) * (SHIP_MAX_VELOCITY),
    -0.3 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(1.0)) * (SHIP_MAX_VELOCITY)
  };
  int sid = rand() % 9999;

  int col = RGB15(rand() % 255, rand() % 255, rand() % 255);

  // Spawn each ship near eachother, around the position spocified
  for (int i = 0; i < shipCount; i++) {
    float size = (rand() % (int)SHIP_MAX_SIZE - 2.0f) + 4.0f;
    int health = size * 10; 
    Vector2 spos = {
      position.x + (rand() % 60 + (- 30)),
      position.y + (rand() % 60 + (- 30))
    };
    Vector2 ssize = {
      size, size
    };

    Ship s = Ship(spos, ssize, enemy, health);

    s.setVelocity(squadVel);
    s.squadId = sid;
    s.color = col;

    world.spawnShip(s);
  }
}

void spawnBattle(SpaceWorld &world, int enemyCount, int allyCount) {}