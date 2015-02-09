#include "PlayerActor.hh"

PlayerActor::PlayerActor() : currentAction(Action::Wait) { }

Action PlayerActor::ChooseAction(){
  return currentAction;
}
