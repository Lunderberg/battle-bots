#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <memory>
#include <vector>

#include "Actor.hh"
#include "Tile.hh"
#include "GameStateView.hh"

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

  //! Returns all tiles and actors seen from a given location.
  /*! @param x The x coordinate of the viewer.
    @param y The y coordinate of the viewer.

    Returns the view as seen by the requested location.
   */
  GameStateView GetTileView(int x, int y) const;
  GameStateView GetTileView() const;

  //! Return the width of the play area.
  int GetWidth() const { return width; }
  //! Return the height of the play area.
  int GetHeight() const { return height; }

  //! Add an actor to the GameState.
  /*! @param actor The actor being added.
    This method also calls Actor::SetGameState to allow the Actor to see.
   */
  void AddActor(std::shared_ptr<Actor> actor);

  bool IsTileEmpty(int x, int y) const;

  //! Returns the actors present in the GameState.
  const std::vector<std::shared_ptr<Actor> >& GetActors() const { return actors; }

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
