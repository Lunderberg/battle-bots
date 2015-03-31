#include "LuaActorStrategy.hh"

#include <lua-bindings/LuaState.hh>

namespace{
  unsigned long max_memory = 512 * 1024;
  int instructions_startup = 10000;
  int instructions_per_frame = 1000;
}

LuaActorStrategy::LuaActorStrategy(const char* filename)
  : active(true) {
  lua = std::unique_ptr<Lua::LuaState>(new Lua::LuaState);
  lua->LoadSafeLibs();

  lua->MakeClass<Action>("Action")
    .AddConstructor<std::string, std::string>("Action");

  lua->MakeClass<Actor>("Actor")
    .AddMethod("GetX", &Actor::GetX)
    .AddMethod("GetY", &Actor::GetY);

  lua->SetGlobal("default", Action(Activity::Wait, Direction::Self));
  lua->SetMaxMemory(max_memory);

  thread = std::unique_ptr<Lua::LuaCoroutine>(new Lua::LuaCoroutine(lua->NewCoroutine()));

  thread->LoadFile(filename);
  thread->SetMaxInstructions(instructions_startup);
  try{
    thread->Resume();
  } catch (LuaException& e) { }
}

LuaActorStrategy::~LuaActorStrategy() { }

Action LuaActorStrategy::ChooseAction() {
  if(!active){
    return Action(Activity::Wait, Direction::Self);
  }

  if(!thread->IsRunning()){
    thread->LoadFunc("choose_action");
    thread->SetMaxInstructions(instructions_per_frame);
  }

  // Return the return value of the lua code, if one exists.
  // If not, return the default value.
  // If the default value cannot be returned, deactivate the bot and wait.
  try{
    return thread->Resume<Action>(actor);
  } catch (LuaException& e) {
    try {
      return lua->CastGlobal<Action>("default");
    } catch (LuaException& e) {
      active = false;
      return Action(Activity::Wait, Direction::Self);
    }
  }
}
