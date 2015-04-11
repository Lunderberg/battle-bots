#ifndef _GAMESTATEVIEW_H_
#define _GAMESTATEVIEW_H_

#include <vector>

#include "Actor.hh"
#include "Tile.hh"

struct TileView{
  TileView(int x, int y, Tile tile)
    : x(x), y(y), tile(tile) { }
  int x,y;
  Tile tile;
};

struct ActorView{
  ActorView(int x, int y, Color color)
    : x(x), y(y), color(color) { }
  int x,y;
  Color color;
};

struct GameStateView{
  std::vector<TileView> tiles;
  std::vector<ActorView> actors;
};

#endif /* _GAMESTATEVIEW_H_ */
