#include <nds.h>
#include "SurfaceWorld.h"

#include <iostream>

SurfaceWorld::SurfaceWorld() {
  int xMax = SCREEN_WIDTH / 16;
  int yMax = SCREEN_HEIGHT / 16;

  for (int i = 0; i < xMax; i++) {
    std::vector<Tile> tempv;

    for (int j = 0; j < yMax; j++) {
      Tile t = Tile();
      t.setColor(RGB15(rand() * 255, rand() * 255, rand() * 255));
      tempv.push_back(t);
    }

    this->tiles.push_back(tempv);
  }
};

void generate() {

}