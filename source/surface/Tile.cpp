#include <nds.h>
#include "Tile.h"
#include <algorithm>

Tile::Tile() {
  this->color = RGB15(rand() % 255, rand() % 255, rand() % 255);
};

void Tile::setColor(int rgb) {
  this->color = rgb;
}

int Tile::getColor() {
  return this->color;
}
