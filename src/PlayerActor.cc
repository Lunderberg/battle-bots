#include "PlayerActor.hh"

PlayerActor::PlayerActor() : currentAction(Activity::Wait, Direction::North) { }

Action PlayerActor::ChooseAction(){
  return currentAction;
}
