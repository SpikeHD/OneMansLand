#include <gl2d.h>

#include "./Renderer.h"

void render(SpaceWorld world, Player player) {
  // Do stuff with the world

  // Draw our player
	glBoxFilled(player.position.x, player.position.y, player.position.x + player.size.x, player.position.y + player.size.y, RGB15(255, 255, 255));
}