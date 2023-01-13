#include <gl2d.h>
#include <algorithm>
#include <iostream>

#include "Renderer.h"

/**
 * Show a triangle pointing to nearby offscreen planets
 */
void renderPlanetTriangle(Planet &planet, SpaceEntityScreenPos &pos, SpacePlayer &player) {
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

SpaceEntityScreenPos SpaceEntityScreenPosition(SpaceWorld &world, SpaceEntity &SpaceEntity, SpacePlayer &player) {
  float zoom = world.zoomLevel;

  // To make a psuedo-camera, we render the player in the middle and the world in relativity to that
  float pPosX = player.getPosition().x;
  float pPosY = player.getPosition().y;
  float pScrPosX = (SCREEN_WIDTH / 2);
  float pScrPosY = (SCREEN_HEIGHT / 2);

  Vector2 center = SpaceEntity.getPosition();
  Vector2 centerOffset {
    (zoom * center.x) - pPosX * zoom,
    (zoom * center.y) - pPosY * zoom
  };

  float sizeX = SpaceEntity.getSize().x * zoom;
  float sizeY = SpaceEntity.getSize().y * zoom;
  float calcXMin = center.x + centerOffset.x + pScrPosX - pPosX - (sizeX / 2);
  float calcYMin = center.y + centerOffset.y + pScrPosY - pPosY - (sizeY / 2);
  float calcXMax = center.x + centerOffset.x + pScrPosX - pPosX + (sizeX / 2);
  float calcYMax = center.y + centerOffset.y + pScrPosY - pPosY + (sizeY / 2);

  return SpaceEntityScreenPos {
    calcXMin,
    calcYMin,
    calcXMax,
    calcYMax
  };
}

void render(SpaceWorld &world, SpacePlayer &player) {
  // TODO: Do stuff with the world
  
  // Draw other ships
  for (Ship &ship : world.ships) {
    SpaceEntityScreenPos epos = SpaceEntityScreenPosition(world, ship, player);
    
    glBoxFilled(
      epos.xMin,
      epos.yMin,
      epos.xMax,
      epos.yMax,
      ship.color
    );
  }

  // Draw projectiles
  for (Projectile &proj : world.projectiles) {
    SpaceEntityScreenPos ppos = SpaceEntityScreenPosition(world, proj, player);
    glBoxFilled(
      ppos.xMin,
      ppos.yMin,
      ppos.xMax,
      ppos.yMax,
      proj.color
    );
  }

  // Draw each planet
  for (Planet &planet : world.planets) {
    SpaceEntityScreenPos plPos = SpaceEntityScreenPosition(world, planet, player);

    // Don't bother drawing if outside of screen
    if (
      plPos.xMax < 0 ||
      plPos.yMax < 0 ||
      plPos.xMin > SCREEN_WIDTH ||
      plPos.yMin > SCREEN_HEIGHT
    ) {
      renderPlanetTriangle(planet, plPos, player);
      continue;
    }

	  glBoxFilled(
      plPos.xMin,
      plPos.yMin,
      plPos.xMax,
      plPos.yMax,
      planet.color
    );
  }

  // Draw our player
	glBoxFilled(
    (SCREEN_WIDTH / 2),
    (SCREEN_HEIGHT / 2),
    ((SCREEN_WIDTH / 2) + player.getSize().x),
    ((SCREEN_HEIGHT / 2) + player.getSize().y),
    player.color
  );
}