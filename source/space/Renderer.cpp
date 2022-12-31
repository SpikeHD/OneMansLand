#include <gl2d.h>

#include "./Renderer.h"

void render(SpaceWorld world, Player player) {
  // Do stuff with the world
  float zoom = world.zoomLevel;

  // To make a psuedo-camera, we render the player in the middle and the world in relativity to that
  float pPosX = player.position.x;
  float pPosY = player.position.y;
  float pScrPosX = (SCREEN_WIDTH / 2);
  float pScrPosY = (SCREEN_HEIGHT / 2);

  // Draw each planet
  for (Planet planet : world.planets) {
    Vector2 center = planet.position;
    float size = planet.size;

	  glBoxFilled(
      (center.x + pScrPosX - pPosX - (size / 2)),
      (center.y + pScrPosY - pPosY - (size / 2)),
      (center.x + pScrPosX - pPosX + (size / 2)),
      (center.y + pScrPosY - pPosY + (size / 2)),
      RGB15(100, 0, 0)
    );
  }

  // Draw our player
	glBoxFilled(
    (SCREEN_WIDTH / 2),
    (SCREEN_HEIGHT / 2),
    ((SCREEN_WIDTH / 2) + player.size.x),
    ((SCREEN_HEIGHT / 2) + player.size.y),
    RGB15(255, 255, 255)
  );
}