#include "Actor.hh"

Actor::Actor() :
  x(0), y(0), state(nullptr), color(0,255,0) { }

Actor::~Actor(){}

void Actor::SetGameState(GameState* game_state){
  state = std::unique_ptr<RestrictedGameState>(new RestrictedGameState(game_state, this));
}
