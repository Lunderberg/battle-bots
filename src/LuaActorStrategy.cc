#include "LuaActorStrategy.hh"

#include <lua-bindings/LuaState.hh>

LuaActorStrategy::LuaActorStrategy(const char* filename){
  lua = std::unique_ptr<Lua::LuaState>(new Lua::LuaState);
  lua->LoadFile(filename);

  lua->MakeClass<Action>("Action")
    .AddConstructor<std::string, std::string>("Action");

  lua->MakeClass<Actor>("Actor")
    .AddMethod("GetX", &Actor::GetX)
    .AddMethod("GetY", &Actor::GetY);
}

LuaActorStrategy::~LuaActorStrategy() { }

Action LuaActorStrategy::ChooseAction() {
  return lua->Call<Action>("choose_action", actor);
}
