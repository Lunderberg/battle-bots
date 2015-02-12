#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <memory>

class GameState;
class RestrictedGameState;

enum class Activity {
  Wait, Move, Attack,
    };
enum class Direction {
  North, East, South, West,
};

struct Action{
  Action(Activity activity = Activity::Wait,
         Direction direction = Direction::North) :
    activity(activity), direction(direction) { }
  Activity activity;
  Direction direction;
};

class Actor{
public:
  Actor();
  virtual ~Actor();
  void Act();

  int GetX() const { return x; }
  int GetY() const { return y; }

  void SetGameState(GameState* state);

protected:
  std::unique_ptr<RestrictedGameState> state;

private:
  virtual Action ChooseAction() = 0;

  int x,y;
};

#endif /* _ACTOR_H_ */
