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

  std::shared_ptr<EventReceiver> receiver;

  double view_scroll_speed;
};

#endif /* _INPUTMANAGER_H_ */
