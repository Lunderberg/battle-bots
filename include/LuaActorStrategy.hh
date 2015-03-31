#ifndef _LUAACTORSTRATEGY_H_
#define _LUAACTORSTRATEGY_H_

#include <memory>

#include "ActorStrategy.hh"

namespace Lua {
  class LuaState;
  class LuaCoroutine;
}

class LuaActorStrategy : public ActorStrategy {
public:
  LuaActorStrategy(const char* filename);
  ~LuaActorStrategy();
  virtual Action ChooseAction();

private:
  bool active;
  std::unique_ptr<Lua::LuaState> lua;
  std::unique_ptr<Lua::LuaCoroutine> thread;
};

#endif /* _LUAACTORSTRATEGY_H_ */
