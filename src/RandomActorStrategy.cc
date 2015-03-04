#include "RandomActorStrategy.hh"

RandomActorStrategy::RandomActorStrategy(std::shared_ptr<std::mt19937> rand) :
  rand(rand) { }

Action RandomActorStrategy::ChooseAction(){
  Action output;
  output.activity = static_cast<Activity>(std::uniform_int_distribution<>(0,2)(*rand));
  output.direction = static_cast<Direction>(std::uniform_int_distribution<>(0,4)(*rand));
  return output;
}
