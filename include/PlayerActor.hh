#ifndef _PLAYERACTOR_H_
#define _PLAYERACTOR_H_

#include "Actor.hh"

class PlayerActor : public Actor {
public:
  PlayerActor();
  virtual Action ChooseAction();
  void SetCurrentAction(Action action){ currentAction = action; }

private:
  Action currentAction;
};

#endif /* _PLAYERACTOR_H_ */
