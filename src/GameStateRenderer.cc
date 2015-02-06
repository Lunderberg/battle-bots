#include "GameStateRenderer.hh"

#include <iostream>

#include <irrlicht.h>

#include "GameState.hh"
GameStateRenderer::GameStateRenderer(std::shared_ptr<GameState> state)
  : state(state), background(NULL), stone(NULL), dirt(NULL) {}

void GameStateRenderer::Draw(irr::video::IVideoDriver* driver){
  int tile_size = 16;

  if(background == NULL){
    background = driver->getTexture("resources/background.png");
  }
  if(stone == NULL){
    stone = driver->getTexture("resources/stone.png");
  }
  if(dirt == NULL){
    dirt = driver->getTexture("resources/dirt.png");
  }

  driver->draw2DImage(background, {0,0});

  for(int i=0; i<state->GetWidth(); i++){
    for(int j=0; j<state->GetHeight(); j++){
      irr::core::position2d<irr::s32> topleft(i*tile_size, j*tile_size);

      switch(state->GetTileAt(i,j)){
      case Tile::Stone:
        driver->draw2DImage(stone, topleft);
        break;

      case Tile::Dirt:
        driver->draw2DImage(dirt, topleft);
        break;
      }
    }
  }
}
