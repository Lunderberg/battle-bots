#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <memory>

class GameState;
class GameStateRenderer;
class EventReceiver;
namespace irr{
  class IrrlichtDevice;
}

class InputManager{
public:
  InputManager(std::shared_ptr<EventReceiver> receiver);
  void HandleInput(irr::IrrlichtDevice* device, GameState& state, GameStateRenderer& renderer);
private:
  void PanViewpoint(irr::IrrlichtDevice* device, GameState& state, GameStateRenderer& renderer);
  void UpdatePlayerActors(GameState& state);

  std::shared_ptr<EventReceiver> receiver;

  double view_scroll_speed;
  unsigned int prev_time;
};

#endif /* _INPUTMANAGER_H_ */
