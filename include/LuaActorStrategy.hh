#ifndef _LUAACTORSTRATEGY_H_
#define _LUAACTORSTRATEGY_H_

#include <memory>

#include "ActorStrategy.hh"

namespace Lua {
  class LuaState;
}

class LuaActorStrategy : public ActorStrategy {
public:
  LuaActorStrategy(const char* filename);
  ~LuaActorStrategy();
  virtual Action ChooseAction();
private:
  std::unique_ptr<Lua::LuaState> lua;
};

#endif /* _LUAACTORSTRATEGY_H_ */
