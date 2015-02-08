#include "GameStateRenderer.hh"

#include <cmath>
#include <iostream>

#include <irrlicht.h>

#include "GameState.hh"
#include "TrapMouse.hh"


GameStateRenderer::GameStateRenderer(std::shared_ptr<GameState> state)
  : state(state),
    background(NULL), stone(NULL), dirt(NULL), outofbounds(NULL),
    tile_size(16), scroll_speed(0.1) {
  center = irr::core::vector2df(state->GetWidth()/2, state->GetHeight()/2);
}

void GameStateRenderer::Update(irr::IrrlichtDevice* device){
  TrapMouse(device);
  PanViewpoint(device);
}

void GameStateRenderer::PanViewpoint(irr::IrrlichtDevice* device){
  auto screen_size = device->getVideoDriver()->getScreenSize();
  int maxX = screen_size.Width;
  int maxY = screen_size.Height;

  auto cursor_pos = device->getCursorControl()->getRelativePosition();
  int x = cursor_pos.X * maxX;
  int y = cursor_pos.Y * maxY;

  if(x<=1 || x>=maxX-2 || y<=1 || y>=maxY-2){
    irr::core::vector2df disp_screen(x - maxX/2, maxY/2 - y);
    disp_screen.normalize();
    center = center + scroll_speed * disp_screen;

    if(center.X < 0){
      center.X = 0;
    } else if (center.X > state->GetWidth()){
      center.X = state->GetWidth();
    }

    if(center.Y < 0){
      center.Y = 0;
    } else if (center.Y > state->GetHeight()){
      center.Y = state->GetHeight();
    }
  }
}

void GameStateRenderer::Draw(irr::video::IVideoDriver* driver){
  if(background == NULL){
    background = driver->getTexture("resources/background.png");
  }
  if(stone == NULL){
    stone = driver->getTexture("resources/stone.png");
  }
  if(dirt == NULL){
    dirt = driver->getTexture("resources/dirt.png");
  }
  if(outofbounds == NULL){
    outofbounds = driver->getTexture("resources/outofbounds.png");
  }

  driver->draw2DImage(background, {0,0});

  auto screen_size = driver->getScreenSize();
  int num_tilesX = screen_size.Width / tile_size + 2;
  int num_tilesY = screen_size.Height / tile_size + 6;
  irr::core::position2d<irr::s32> center_tile{
    int(std::floor(center.X)), int(std::floor(center.Y))
  };

  double temp;
  irr::core::position2d<irr::s32> center_position{
    int(screen_size.Width/2.0  - tile_size * std::modf(center.X, &temp)),
    int(screen_size.Height/2.0 + tile_size * std::modf(center.Y, &temp))
  };


  for(int i = -num_tilesX/2; i<num_tilesX/2; i++){
    for(int j = -num_tilesY/2; j<num_tilesY/2; j++){

      irr::core::position2d<irr::s32> topleft( i*tile_size + center_position.X,
                                              -j*tile_size + center_position.Y);
      irr::core::rect<irr::s32> dest_rect(topleft.X, topleft.Y,
                                          topleft.X + tile_size, topleft.Y + tile_size);
      irr::core::rect<irr::s32> source_rect(0, 0, 16, 16);
      irr::video::ITexture* image = NULL;


      switch(state->GetTileAt(center_tile.X + i, center_tile.Y + j)){
      case Tile::Stone:
        image = stone;
        break;
      case Tile::Dirt:
        image = dirt;
        break;
      case Tile::OutOfBounds:
        image = outofbounds;
        break;
      }

      if(image != NULL){
        //driver->draw2DImage(image, topleft);
        driver->draw2DImage(image, dest_rect, source_rect);
      }

    }
  }
}
