#ifndef _ACTOR_H_
#define _ACTOR_H_

enum class Action {
  Wait,
    MoveLeft, MoveRight, MoveUp, MoveDown,
    AttackLeft, AttackRight, AttackUp, AttackDown,
    };


class Actor{
public:
  Actor();
  virtual ~Actor();
  virtual Action ChooseAction() = 0;
  void Act();

  int GetX() const { return x; }
  int GetY() const { return y; }

private:
  int x,y;
};

#endif /* _ACTOR_H_ */
