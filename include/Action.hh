#ifndef _ACTION_H_
#define _ACTION_H_

enum class Activity {
  Wait, Move, Attack,
    };
enum class Direction {
  North, East, South, West, Self,
};

//! A container for the desired action that an Actor will perform each frame.
struct Action{
  Action(Activity activity = Activity::Wait,
         Direction direction = Direction::North) :
    activity(activity), direction(direction) { }
  Activity activity;
  Direction direction;
};

#endif /* _ACTION_H_ */