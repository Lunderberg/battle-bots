#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <memory>
#include <vector>

#include "Actor.hh"
#include "Tile.hh"

class GameState{
public:
  GameState(int width, int height);
  void FrameUpdate();

  Tile GetTileAt (int i, int j) const;
  int GetWidth() const { return width; }
  int GetHeight() const { return height; }

  void AddActor(std::shared_ptr<Actor> actor);
  const std::vector<std::shared_ptr<Actor> >& GetActors(){ return actors; }
  std::vector<std::shared_ptr<const Actor> > GetActors() const {
    return std::vector<std::shared_ptr<const Actor> >(actors.begin(), actors.end());
  }

private:
  int width;
  int height;

  std::vector<Tile> map;
  std::vector<std::shared_ptr<Actor> > actors;
};

#endif /* _GAMESTATE_H_ */
