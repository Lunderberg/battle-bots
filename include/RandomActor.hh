#ifndef _RANDOMACTOR_H_
#define _RANDOMACTOR_H_

#include <memory>
#include <random>

#include "Actor.hh"

class RandomActor : public Actor {
public:
  RandomActor(std::shared_ptr<std::mt19937> rand);
  virtual Action ChooseAction();

private:
  std::shared_ptr<std::mt19937> rand;
};

#endif /* _RANDOMACTOR_H_ */
