#include <nds.h>
#include "SurfaceWorld.h"

SurfaceWorld::SurfaceWorld() {
  int xMax = SCREEN_WIDTH / 16;
  int yMax = SCREEN_HEIGHT / 16;

  for (int i = 0; i < xMax; i++) {
    for (int j = 0; j < yMax; j++) {
      Tile t = Tile();
      this->tiles.at(i).push_back(t);
    }
  }
};

void generate() {

}