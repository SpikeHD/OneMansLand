#include <gl2d.h>
#include "SurfaceRenderer.h"

#include <iostream>

void surfaceRender(SurfaceWorld &world) {
  int tileSizePx = 16;
  int tileRow = 0;
  int tileCol = 0;

  // Render tiles on screen
  for (int i = 0; i < world.tiles.size(); i++) {
    std::vector<Tile> tilesAt = world.tiles.at(i);

    for (int j = 0; j < tilesAt.size(); j++) {
      glBoxFilled(i * tileSizePx, j * tileSizePx, i + tileSizePx, j + tileSizePx, RGB15(255,255,255));
    }
  }
}