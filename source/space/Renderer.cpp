#include <gl2d.h>
#include <algorithm>
#include <iostream>

#include "Renderer.h"

/**
 * Show a triangle pointing to nearby offscreen planets
 */
void renderPlanetTriangle(Planet planet, PlanetPosition pos, SpacePlayer player) {
  Vector2 pCenter {
    pos.xMax - ((pos.xMax - pos.xMin) / 2),
    pos.yMax - ((pos.yMax - pos.yMin) / 2)
  };

  // These are screen coordinates, not world corrdinates
  float tipX = clamp((int)pCenter.x, 0, SCREEN_WIDTH);
  float tipY = clamp((int)pCenter.y, 0, SCREEN_HEIGHT);
  float size = 10 - clamp((int)(planet.distanceFrom(player) * 0.02), 0, 8);

  if (tipX == SCREEN_WIDTH) tipX -= size;
  if (tipY == SCREEN_HEIGHT) tipY -= size;

  //glTriangleFilled(tipX, tipY, );
  glBoxFilled(tipX, tipY, tipX + size, tipY + size, RGB15(255,255,255));
}

PlanetPosition planetScreenPosition(SpaceWorld world, Planet planet, SpacePlayer player) {
  float zoom = world.zoomLevel;

  // To make a psuedo-camera, we render the player in the middle and the world in relativity to that
  float pPosX = player.position.x;
  float pPosY = player.position.y;
  float pScrPosX = (SCREEN_WIDTH / 2);
  float pScrPosY = (SCREEN_HEIGHT / 2);

  Vector2 center = planet.position;
  Vector2 centerOffset {
    (zoom * center.x) - pPosX * zoom,
    (zoom * center.y) - pPosY * zoom
  };

  float size = planet.size.x * zoom;
  float calcXMin = center.x + centerOffset.x + pScrPosX - pPosX - (size / 2);
  float calcYMin = center.y + centerOffset.y + pScrPosY - pPosY - (size / 2);
  float calcXMax = center.x + centerOffset.x + pScrPosX - pPosX + (size / 2);
  float calcYMax = center.y + centerOffset.y + pScrPosY - pPosY + (size / 2);

  return PlanetPosition {
    calcXMin,
    calcYMin,
    calcXMax,
    calcYMax
  };
}

void render(SpaceWorld world, SpacePlayer player) {
  // TODO: Do stuff with the world

  // Draw each planet
  for (Planet planet : world.planets) {
    PlanetPosition pos = planetScreenPosition(world, planet, player);

    // Don't bother drawing if outside of screen
    if (
      pos.xMax < 0 ||
      pos.yMax < 0 ||
      pos.xMin > SCREEN_WIDTH ||
      pos.yMin > SCREEN_HEIGHT
    ) {
      renderPlanetTriangle(planet, pos, player);
      continue;
    }

	  glBoxFilled(
      pos.xMin,
      pos.yMin,
      pos.xMax,
      pos.yMax,
      planet.color
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