#ifndef _ACTORSTRATEGY_H_
#define _ACTORSTRATEGY_H_

#include <cassert>

class Actor;
#include "Action.hh"

class ActorStrategy{
  friend class Actor;
public:
  ActorStrategy() : actor(nullptr) { }
  virtual ~ActorStrategy() { }
  virtual Action ChooseAction() = 0;
protected:
  const Actor& GetActor() { return *actor; }
private:
  void SetActor(Actor* actor) {
    assert(actor != nullptr);
    this->actor = actor;
  }
  Actor* actor;
};

#endif /* _ACTORSTRATEGY_H_ */
