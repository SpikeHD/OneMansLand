#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

// Our stuff
#include "./space/entity/Player.h"
#include "./space/Renderer.h"
#include "./space/SpaceWorld.h"

volatile int frame = 0;

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
  Vector2 initialPos;
  initialPos.x = 0;
  initialPos.y = 0;

  Vector2 size;
  size.x = 5;
  size.y = 5;

  // The player
  Player player = Player(initialPos, size);

  // The spaceworld
  SpaceWorld world = SpaceWorld();

  // Initializes GL2D and stuff
  gl2dInit();
  
  // TODO: this is for debugging only
	consoleDemoInit();
  iprintf("This is a test");

  while(1) {
    glBegin2D();

    render(world, player);

    glEnd2D();
		glFlush(0);

		swiWaitForVBlank();
  }
}