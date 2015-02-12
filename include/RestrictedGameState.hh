#ifndef _RESTRICTEDGAMESTATE_H_
#define _RESTRICTEDGAMESTATE_H_

class GameState;
class Actor;

class RestrictedGameState{
public:
  RestrictedGameState(GameState* game_state, Actor* actor)
    : state(game_state), actor(actor) { }

private:
  GameState* state;
  Actor* actor;
};

#endif /* _RESTRICTEDGAMESTATE_H_ */
