#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <memory>

#include "RestrictedGameState.hh"

class GameState;

enum class Activity {
  Wait, Move, Attack,
    };
enum class Direction {
  North, East, South, West,
};

//! A container for the desired action that an Actor will perform each frame.
struct Action{
  Action(Activity activity = Activity::Wait,
         Direction direction = Direction::North) :
    activity(activity), direction(direction) { }
  Activity activity;
  Direction direction;
};

struct Color{
  Color(unsigned char red, unsigned char green, unsigned char blue) :
    red(red), green(green), blue(blue) { }
  unsigned char red, green, blue;
};

//! The base class of all independent actors
class Actor{
  friend class GameState;
public:
  Actor();
  virtual ~Actor();

  //! Returns the x position of the actor.
  int GetX() const { return x; }
  //! Returns the y position of the actor.
  int GetY() const { return y; }
  //! Returns the color of the actor.
  Color GetColor() const { return color; }
  void SetColor(Color color_in) { color = color_in; }

  //! Sets the internal gamestate known by the actor.
  /*! @param game_state The full state of the game.

    This will construct the protected variable state.
   */
  void SetGameState(GameState* game_state);

protected:
  //! The RestrictedGameState held by the current Actor
  /*!
    Contains a view into the full GameState, containing only what the current Actor can see.
    At initialization, state contains a nullptr.
    After being added to a GameState, shows a valid RestrictedGameState.
   */
  std::unique_ptr<RestrictedGameState> state;

private:
  //! Selects the action to be taken by the actor.
  /*! Given the current state of the game, choose an action to take on this frame.
   */
  virtual Action ChooseAction() = 0;

  void SetX(int x) { this->x = x; }
  void SetY(int y) { this->y = y; }

  int x,y; //! The current position of the Actor.
  Color color; //! The current color of the Actor.
};

#endif /* _ACTOR_H_ */
