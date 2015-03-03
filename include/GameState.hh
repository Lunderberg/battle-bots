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

  //! Returns the type of tile present at a given location.
  /*! @param x The x coordinate of the desired tile.
    @param y The y coordinate of the desired tile.

    Return the tile present at the given location.
    Returns Tile::OutOfBounds if the requested location is outside of the full map.
   */
  Tile GetTileAt(int x, int y) const;
  //! Return the width of the play area.
  int GetWidth() const { return width; }
  //! Return the height of the play area.
  int GetHeight() const { return height; }

  //! Add an actor to the GameState.
  /*! @param actor The actor being added.
    This method also calls Actor::SetGameState to allow the Actor to see.
   */
  void AddActor(std::unique_ptr<Actor> actor);

  //! Returns the actors present in the GameState.
  const std::vector<std::shared_ptr<Actor> >& GetActors(){ return actors; }
  //! Returns the actors present in the GameState.
  std::vector<std::shared_ptr<const Actor> > GetActors() const {
    return std::vector<std::shared_ptr<const Actor> >(actors.begin(), actors.end());
  }

private:
  void SetTileAt(Tile tile, int x, int y);

  void UpdateActor(Actor& actor);
  void ActorMove(Actor& actor, int target_x, int target_y);
  void ActorWait(Actor& actor);
  void ActorAttack(Actor& actor, int target_x, int target_y);

  int width;
  int height;

  std::vector<Tile> map;
  std::vector<std::shared_ptr<Actor> > actors;
};

#endif /* _GAMESTATE_H_ */
