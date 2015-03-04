#ifndef _NULLACTORSTRATEGY_H_
#define _NULLACTORSTRATEGY_H_

#include "ActorStrategy.hh"

class NullActorStrategy : public ActorStrategy {
public:
  NullActorStrategy() { }
  virtual Action ChooseAction(){
    return {Activity::Wait};
  }
};

#endif /* _NULLACTORSTRATEGY_H_ */
