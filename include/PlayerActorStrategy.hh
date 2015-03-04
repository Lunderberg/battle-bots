#ifndef _PLAYERACTORSTRATEGY_H_
#define _PLAYERACTORSTRATEGY_H_

#include "ActorStrategy.hh"

class PlayerActorStrategy : public ActorStrategy {
public:
  PlayerActorStrategy();
  virtual Action ChooseAction();
  void SetCurrentAction(Action action){ currentAction = action; }

private:
  Action currentAction;
};

#endif /* _PLAYERACTORSTRATEGY_H_ */
