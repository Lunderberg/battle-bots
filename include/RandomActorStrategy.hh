#ifndef RANDOMACTORSTRATEGY_H_
#define RANDOMACTORSTRATEGY_H_

#include <memory>
#include <random>

#include "ActorStrategy.hh"

class RandomActorStrategy : public ActorStrategy {
public:
  RandomActorStrategy(std::shared_ptr<std::mt19937> rand);
  virtual Action ChooseAction();

private:
  std::shared_ptr<std::mt19937> rand;
};

#endif /* RANDOMACTORSTRATEGY_H_ */
