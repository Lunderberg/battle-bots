#include "Actor.hh"

#include "NullActorStrategy.hh"

Actor::Actor() :
  x(0), y(0), game_state(nullptr), color(0,255,0),
  strategy(std::unique_ptr<ActorStrategy>(new NullActorStrategy)) { }

Actor::~Actor(){}

void Actor::SetGameState(GameState* game_state){
  this->game_state = game_state;
}
