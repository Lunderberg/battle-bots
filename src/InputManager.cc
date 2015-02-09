#include "InputManager.hh"

#include <irrlicht.h>

#include "EventReceiver.hh"
#include "GameState.hh"
#include "GameStateRenderer.hh"
#include "PlayerActor.hh"
#include "Utilities.hh"

InputManager::InputManager(std::shared_ptr<EventReceiver> receiver)
  : receiver(receiver), view_scroll_speed(0.1) {}

void InputManager::HandleInput(irr::IrrlichtDevice* device, GameState& state, GameStateRenderer& renderer){
  PanViewpoint(device, state, renderer);
  UpdatePlayerActors(state);
}

void InputManager::PanViewpoint(irr::IrrlichtDevice* device, GameState& state, GameStateRenderer& renderer){
  auto screen_size = device->getVideoDriver()->getScreenSize();
  int maxX = screen_size.Width;
  int maxY = screen_size.Height;

  auto cursor_pos = device->getCursorControl()->getRelativePosition();
  int x = cursor_pos.X * maxX;
  int y = cursor_pos.Y * maxY;

  // Trap the mouse within the window.
  bool changedX = clamp_modify(x, 1, maxX-2);
  bool changedY = clamp_modify(y, 1, maxY-2);
  if(changedX || changedY){
    device->getCursorControl()->setPosition(x,y);
  }

  // Pan the viewpoint if the mouse is at the edge of the window.
  if(x<=1 || x>=maxX-2 || y<=1 || y>=maxY-2){
    // dY is reversed because GameState coordinates have +y going up,
    //    while irrlicht screen coordinates have +y going down.
    irr::core::vector2df disp_screen(x - maxX/2, maxY/2 - y);
    disp_screen.normalize();
    auto center = renderer.GetCenter() + view_scroll_speed * disp_screen;
    clamp_modify(center.X, 0, state.GetWidth());
    clamp_modify(center.Y, 0, state.GetHeight());
    renderer.SetCenter(center);
  }

  if(receiver->GetMouseWheel()){
    renderer.SetTileSize( renderer.GetTileSize() + receiver->GetMouseWheel() );
    receiver->ResetMouseWheel();
  }
}

void InputManager::UpdatePlayerActors(GameState& state){
  Action action = Action::Wait;
  if(receiver->IsKeyDown(irr::KEY_KEY_W)){
    action = Action::MoveUp;
  } else if(receiver->IsKeyDown(irr::KEY_KEY_S)){
    action = Action::MoveDown;
  } else if(receiver->IsKeyDown(irr::KEY_KEY_A)){
    action = Action::MoveLeft;
  } else if(receiver->IsKeyDown(irr::KEY_KEY_D)){
    action = Action::MoveRight;
  }

  for(auto& actor : state.GetActors()){
    auto player_actor = std::dynamic_pointer_cast<PlayerActor>(actor);
    if(player_actor){
      player_actor->SetCurrentAction(action);
    }
  }
}
