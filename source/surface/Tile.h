#ifndef SUR_TILE_H
#define SUR_TILE_H

class Tile {
  public:
    Tile();

    void setColor(int);
    int getColor();

  private:
    int color;
};

#endif