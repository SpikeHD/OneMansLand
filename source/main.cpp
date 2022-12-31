#include <nds.h>
#include <gl2d.h>
#include <iostream>

// Our stuff
#include "controls.h"
#include "space/entity/SpacePlayer.h"
#include "space/Renderer.h"
#include "space/SpaceWorld.h"

volatile int frame = 0;

enum WorldState {
  WS_SPACE,
  WS_PLANET
};

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
  WorldState state = WS_SPACE;

  Vector2 initialPos;
  initialPos.x = 0;
  initialPos.y = 0;

  Vector2 size;
  size.x = 5;
  size.y = 5;

  // The space player
  SpacePlayer player = SpacePlayer(initialPos, size);

  // The spaceworld
  SpaceWorld world = SpaceWorld();
  world.generate();

  // Initializes GL2D and stuff
  gl2dInit();
  
  // TODO: this is for debugging only
	consoleDemoInit();
  iprintf("This is a test");

  while(1) {
    // Scan for control presses
    scanKeys();

    glBegin2D();

    // We have landed! Change the world state to begin rendering the planet surface stuffand handling controls differently
    if (world.landedOnPlanet) {
      state = WS_PLANET;
    }

    if (state == WS_SPACE) {
      render(world, player);
      player.control(world);
      player.update(world);
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