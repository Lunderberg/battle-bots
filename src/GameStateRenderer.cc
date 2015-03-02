#include "GameStateRenderer.hh"

#include <cmath>
#include <iostream>
#include <limits>

#include <irrlicht.h>

#include "GameState.hh"


GameStateRenderer::GameStateRenderer(const GameState& state)
  : background(NULL), stone(NULL), dirt(NULL), outofbounds(NULL), actor_texture(NULL),
    tile_size(16), scroll_speed(0.1){
  center = irr::core::vector2df(state.GetWidth()/2.0, state.GetHeight()/2.0);
}

void GameStateRenderer::Draw(irr::video::IVideoDriver* driver, const GameState& state){
  InitializeTextures(driver);

  driver->draw2DImage(background, {0,0});

  auto screen_size = driver->getScreenSize();
  int num_tilesX = screen_size.Width / tile_size + 6;
  int num_tilesY = screen_size.Height / tile_size + 6;
  irr::core::position2d<irr::s32> center_tile{
    int(std::floor(center.X)), int(std::floor(center.Y))
  };

  double temp;
  irr::core::position2d<irr::s32> center_position{
    int(screen_size.Width/2.0  - tile_size * std::modf(center.X, &temp)),
    int(screen_size.Height/2.0 + tile_size * std::modf(center.Y, &temp))
  };


  // Draw all active tiles
  for(int i = -num_tilesX/2; i<num_tilesX/2; i++){
    for(int j = -num_tilesY/2; j<num_tilesY/2; j++){

      irr::core::position2d<irr::s32> topleft( i*tile_size + center_position.X,
                                              -j*tile_size + center_position.Y);
      irr::core::rect<irr::s32> dest_rect(topleft.X, topleft.Y,
                                          topleft.X + tile_size, topleft.Y + tile_size);
      irr::core::rect<irr::s32> source_rect(0, 0, 16, 16);
      irr::video::ITexture* image = NULL;


      switch(state.GetTileAt(center_tile.X + i, center_tile.Y + j)){
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
        driver->draw2DImage(image, dest_rect, source_rect,
                            NULL, NULL, true);
      }
    }
  }

  // Draw all actors
  for(auto& actor : state.GetActors()){
    int i = actor->GetX() - center_tile.X;
    int j = actor->GetY() - center_tile.Y;
    auto color = actor->GetColor();

    irr::core::position2d<irr::s32> topleft( i*tile_size + center_position.X,
                                             -j*tile_size + center_position.Y);
    irr::core::rect<irr::s32> dest_rect(topleft.X, topleft.Y,
                                        topleft.X + tile_size, topleft.Y + tile_size);
    irr::core::rect<irr::s32> source_rect(0, 0, 16, 16);
    if(actor_texture != NULL){
      std::vector<irr::video::SColor> colors;
      colors.resize(4, {255, color.red, color.green, color.blue} );
      driver->draw2DImage(actor_texture, dest_rect, source_rect,
                          NULL, colors.data() , true);
    }
  }
}

void GameStateRenderer::InitializeTextures(irr::video::IVideoDriver* driver){
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
  if(actor_texture == NULL){
    actor_texture = driver->getTexture("resources/actor.png");
    //driver->makeColorKeyTexture(actor_texture, {0,0});
  }
}
