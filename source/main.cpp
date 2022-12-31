#include <nds.h>
#include <gl2d.h>
#include <iostream>
#include <algorithm>

// Our stuff
#include "./controls.h"
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

void controlPlayer(Player &player, SpaceWorld &world) {
  cout << "Keys pressed: ";

  if (btn_up()) {
    player.addYVelocity(-0.05);
    cout << "^ ";
  }

  if (btn_down()) {
    player.addYVelocity(0.05);
    cout << "v ";
  }

  if (btn_right()) {
    player.addXVelocity(0.05);
    cout << "> ";
  }

  if (btn_left()) {
    player.addXVelocity(-0.05);
    cout << "< ";
  }

  // Zooming in and out
  if (btn_rbump()) {
    world.zoomLevel = std::clamp(world.zoomLevel + 0.05f, 1.0f, 2.0f);
    cout << "RB ";
  }

  // Zooming in and out
  if (btn_lbump()) {
    world.zoomLevel = std::clamp(world.zoomLevel - 0.05f, 1.0f, 2.0f);
    cout << "LB ";
  }

  cout << endl;
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
  world.generate();

  // Initializes GL2D and stuff
  gl2dInit();
  
  // TODO: this is for debugging only
	consoleDemoInit();
  iprintf("This is a test");

  while(1) {
    // Scan for control presses
    scanKeys();
    controlPlayer(player, world);

    glBegin2D();

    render(world, player);

    player.update(world);

    glEnd2D();
		glFlush(0);

		swiWaitForVBlank();

    consoleClear();
  }
}