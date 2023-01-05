#include <nds.h>
#include <gl2d.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cmath>

// Our stuff
#include "consts.h"
#include "controls.h"
#include "space/entity/SpacePlayer.h"
#include "space/entity/Ship.h"
#include "space/Renderer.h"
#include "space/SpaceWorld.h"
#include "space/entity/Squad.h"

// For tickrate
volatile time_t processedTime;
int frame = 0;

enum WorldState {
  WS_SPACE,
  WS_PLANET
};

time_t curTimeT() {
  return time(NULL);
}

void Vblank() {
  frame++;
}

void gl2dInit() {
  // Initialize GL2D
	irqSet(IRQ_VBLANK, Vblank);

	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_0_2D);

	glScreen2D();
}

int main(void) {
  processedTime = curTimeT();
  // Init RNG
  srand(processedTime);

  int canShootAgainFrame = 0;
  touchPosition touchXY;

  WorldState state = WS_SPACE;
  Vector2 initialPos = {
    0.0f, 0.0f
  };
  Vector2 size = {
    5.0f, 5.0f
  };
  // The space player
  SpacePlayer player = SpacePlayer(initialPos, size);
  // The spaceworld
  SpaceWorld world = SpaceWorld();
  world.generate();

  // DEBUG
  Vector2 enPos = {
    30.0f, 30.0f
  };
  Ship enemy = Ship(enPos, size, true, 50);

  enemy.addXVelocity(0.1f);

  // DEBUG
  world.spawnShip(enemy);

  // Initializes GL2D and stuff
  gl2dInit();
  
  // TODO: this is for debugging only
	consoleDemoInit();

  // DEBUG
  int lastFrame = 0;
  int fps = 0;

  // TESTING
  spawnSquad(world, 3, false, initialPos);

  while(1) {
    // Scan for control presses
    scanKeys();
    touchRead(&touchXY);

    glBegin2D();

    // For debugging, can remove later
    if (std::difftime(curTimeT(), processedTime) > 1) {
      fps = frame - lastFrame;

      processedTime = curTimeT();
      lastFrame = frame;
    }

    cout << "FPS: " << fps << endl;

    // We have landed! Change the world state to begin rendering the planet surface stuff and handling controls differently
    if (world.landedOnPlanet) {
      state = WS_PLANET;
    }

    if (state == WS_SPACE) {
      cout << "World projectiles: " << world.projectiles.size() << endl;

      render(world, player);

      player.control(world);
      player.update(world);
      world.update(player);

      if (touchXY.px != 0 && touchXY.py != 0) {
        if (canShootAgainFrame != 0 && canShootAgainFrame < frame) {
          // Check if the cooldown for the weapon has ended
          canShootAgainFrame = 0;
        }

        if (canShootAgainFrame == 0) {
          // Calc angle from the center of the screen
          Vector2 center {
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2
          };
          Vector2 touchVec {
            touchXY.px,
            touchXY.py
          };
          
          canShootAgainFrame = frame + player.shoot(world, angleFrom(touchVec, center));
        }
      }
    }

    if (state == WS_PLANET) {
      // TODO
    }

    glEnd2D();
    glFlush(0);

    swiWaitForVBlank();

    consoleClear();
  }
}