#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <memory>

#include "Action.hh"
#include "ActorStrategy.hh"

class GameState;

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
  void SetGameState(GameState* game_state);

  template<typename Strategy, typename... Params>
  void MakeStrategy(Params&&... params){
    strategy = std::unique_ptr<ActorStrategy>(new Strategy(std::forward<Params>(params)...));
    strategy->SetActor(this);
  }
  ActorStrategy* GetStrategy(){return strategy.get();}

  Action ChooseAction(){ return strategy->ChooseAction(); }

private:
  void SetX(int x) { this->x = x; }
  void SetY(int y) { this->y = y; }

  int x,y; //! The current position of the Actor.
  Color color; //! The current color of the Actor.
  GameState* game_state; //! Pointer to the GameState which holds this Actor.
  std::unique_ptr<ActorStrategy> strategy;
};

#endif /* _ACTOR_H_ */
