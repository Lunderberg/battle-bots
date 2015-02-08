#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

#include <irrlicht.h>
#include "driverChoice.h"

#include "EventReceiver.hh"
#include "PanningCamera.hh"
#include "ProceduralTexture.hh"
#include "TrapMouse.hh"

#include "GameState.hh"
#include "GameStateRenderer.hh"

using namespace irr;

int main(){
  EventReceiver receiver;
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640,480), 16,
        		     false, true, false, &receiver);
  if (!device){
    return 1;
  }

  device->setWindowCaption(L"2D Graphics test");

  auto driver = device->getVideoDriver();
  auto smgr = device->getSceneManager();
  auto guienv = device->getGUIEnvironment();

  // Load the sprites
  video::ITexture* images = driver->getTexture("resources/2ddemo.png");
  driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

  // Load the fonts
  gui::IGUIFont* font = guienv->getBuiltInFont();
  gui::IGUIFont* font2 = guienv->getFont("resources/fonthaettenschweiler.bmp");

  auto game_state = std::make_shared<GameState>(20,20);
  GameStateRenderer game_state_renderer(game_state);

  // A 2d render mode
  driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
  driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

  u32 prev_time = device->getTimer()->getTime();

  while(device->run() && driver){
    // Find dT
    auto now = device->getTimer()->getTime();
    double dT = (now - prev_time) / 1000.0;
    prev_time = now;

    if(!device->isWindowActive()){
      device->yield();
      continue;
    }

    driver->beginScene(true, true, video::SColor(255,120,102,136));

    game_state_renderer.Update(device);
    game_state_renderer.Draw(driver);




    // driver->enableMaterial2D();
    // driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
    //                     core::rect<s32>(354,87,442,118));
    // driver->enableMaterial2D(false);

    core::position2d<s32> mouse = device->getCursorControl()->getPosition();
    driver->draw2DRectangle(video::SColor(100,255,255,255),
                            core::rect<s32>(mouse.X-20, mouse.Y-20, mouse.X+20, mouse.Y+20));

    driver->endScene();
  }

  device->drop();
  return 0;
}
