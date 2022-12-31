#include <gl2d.h>

#include "./Renderer.h"

void render(SpaceWorld world, Player player) {
  // Do stuff with the world

  // Draw each planet
  for (Planet planet : world.planets) {
    Vector2 center = planet.position;
    float size = planet.size;

	  glBoxFilled(
      center.x - (size / 2),
      center.y - (size / 2),
      center.x + (size / 2),
      center.y + (size / 2),
      RGB15(100, 0, 0)
    );
  }

  // Draw our player
	glBoxFilled(player.position.x, player.position.y, player.position.x + player.size.x, player.position.y + player.size.y, RGB15(255, 255, 255));
}