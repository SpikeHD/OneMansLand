#include "Renderer.h"

#include <iostream>

void render(SurfaceWorld world) {
  int tileSizePx = 16;
  int tileRow = 0;
  int tileCol = 0;

  // Render tiles on screen
  for (int i = 0; i < world.tiles.size(); i++) {
    std::vector<Tile> tilesAt = world.tiles.at(i);

    for (int j = 0; j < tilesAt.size(); j++) {
      printf("Drawing square at x=%f y=%f", i * 16, j * 16);
    }
  }
}