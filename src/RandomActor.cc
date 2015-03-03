#include "RandomActor.hh"

RandomActor::RandomActor(std::shared_ptr<std::mt19937> rand) :
  rand(rand) { }

Action RandomActor::ChooseAction(){
  Action output;
  output.activity = static_cast<Activity>(std::uniform_int_distribution<>(0,2)(*rand));
  output.direction = static_cast<Direction>(std::uniform_int_distribution<>(0,4)(*rand));
  return output;
}
