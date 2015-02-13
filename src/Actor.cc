#include "Actor.hh"

Actor::Actor() : x(0), y(0), state(nullptr) { }

Actor::~Actor(){}

void Actor::SetGameState(GameState* game_state){
  state = std::unique_ptr<RestrictedGameState>(new RestrictedGameState(game_state, this));
}
