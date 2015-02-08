#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <memory>
#include <vector>

#include "Tile.hh"

class GameState{
public:
  GameState(int width, int height);
  Tile GetTileAt (int i, int j) const;
  int GetWidth() const {return width;}
  int GetHeight() const {return height;}

private:
  int width;
  int height;

  std::vector<Tile> map;
  //std::vector<std::shared_ptr<Actor> > actors;
};

#endif /* _GAMESTATE_H_ */