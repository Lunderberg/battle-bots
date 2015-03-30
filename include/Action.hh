#ifndef _ACTION_H_
#define _ACTION_H_

#include <string>

enum class Activity {
  Wait, Move, Attack,
    };
enum class Direction {
  North, East, South, West, Self,
};

//! A container for the desired action that an Actor will perform each frame.
struct Action{
  Activity activity;
  Direction direction;

  Action(Activity activity = Activity::Wait,
         Direction direction = Direction::North) :
    activity(activity), direction(direction) { }

  Action(std::string activity, std::string direction){
    if(activity == "Move") {
      this->activity = Activity::Move;
    } else if (activity == "Attack") {
      this->activity = Activity::Attack;
    } else {
      this->activity = Activity::Wait;
    }

    if(direction == "North"){
      this->direction = Direction::North;
    } else if(direction == "South"){
      this->direction = Direction::South;
    } else if(direction == "East"){
      this->direction = Direction::East;
    } else if(direction == "West"){
      this->direction = Direction::West;
    } else {
      this->direction = Direction::Self;
    }
  }

  bool operator==(const Action& other) const {
    return (activity == other.activity) &&
      (direction == other.direction);
  }
  bool operator!=(const Action& other) const {
    return !(*this == other);
  }
};

#endif /* _ACTION_H_ */
