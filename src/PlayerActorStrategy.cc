#include "PlayerActorStrategy.hh"

PlayerActorStrategy::PlayerActorStrategy() : currentAction(Activity::Wait, Direction::North) { }

Action PlayerActorStrategy::ChooseAction(){
  return currentAction;
}
