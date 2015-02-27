#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

#include <irrlicht.h>

#include "EventReceiver.hh"
#include "GameState.hh"
#include "GameStateRenderer.hh"
#include "InputManager.hh"
#include "PlayerActor.hh"

using namespace irr;

int main(){
  const bool show_fps = true;
  const double gamestate_fps = 30;

  auto receiver = std::make_shared<EventReceiver>();
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640,480), 16,
                                        false, true, true, receiver.get());
  if (!device){
    return 1;
  }

  device->setWindowCaption(L"2D Graphics test");

  auto driver = device->getVideoDriver();
  auto smgr = device->getSceneManager();
  auto guienv = device->getGUIEnvironment();

  irr::gui::IGUIFont* font = guienv->getBuiltInFont();

  GameState game_state(20,20);
  GameStateRenderer game_state_renderer(game_state);
  InputManager input_manager(receiver);

  game_state.AddActor(std::unique_ptr<Actor>(new PlayerActor));

  // // Uncomment to use bilinear filter for resizing.
  // driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
  // driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;
  // driver->enableMaterial2D();

  int game_steps = 0;
  while(device->run() && driver){
    if(!device->isWindowActive()){
      device->yield();
      continue;
    }

    // Read input
    input_manager.HandleInput(device, game_state, game_state_renderer);

    // Update game state
    int desired_game_steps = device->getTimer()->getTime() * (gamestate_fps / 1000.0);
    while(game_steps < desired_game_steps){
      game_state.FrameUpdate();
      game_steps++;
    }

    // Draw
    driver->beginScene(true, true, video::SColor(255,120,102,136));

    game_state_renderer.Draw(driver, game_state);

    core::position2d<s32> mouse = device->getCursorControl()->getPosition();
    driver->draw2DRectangle(video::SColor(100,255,255,255),
                            core::rect<s32>(mouse.X-20, mouse.Y-20, mouse.X+20, mouse.Y+20));

    if(font && show_fps){
      std::wstringstream ss;
      ss << "FPS: " << driver->getFPS();
      auto fps_string = ss.str();
      font->draw(fps_string.c_str(),
                 irr::core::rect<s32>(130, 10, 300, 50),
                 irr::video::SColor(255,255,255,255));
    }

    driver->endScene();
  }

  device->drop();
  return 0;
}
