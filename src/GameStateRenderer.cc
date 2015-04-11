#include "GameStateRenderer.hh"

#include <cmath>
#include <iostream>
#include <limits>

#include <irrlicht.h>

#include "GameState.hh"


GameStateRenderer::GameStateRenderer(const GameState& state)
  : background(NULL), stone(NULL), dirt(NULL), outofbounds(NULL),
    actor_texture(NULL), empty(NULL), unseen(NULL),
    tile_size(16), scroll_speed(0.1){
  center = irr::core::vector2df(state.GetWidth()/2.0, state.GetHeight()/2.0);
}

void GameStateRenderer::Draw(irr::video::IVideoDriver* driver, const GameState& state){
  InitializeTextures(driver);

  driver->draw2DImage(background, {0,0});

  auto screen_size = driver->getScreenSize();

  irr::core::position2d<irr::s32> origin(
    screen_size.Width/2  - tile_size*center.X,
    screen_size.Height/2 + tile_size*center.Y
  );

  auto actor = viewed_from.lock();
  GameStateView view = actor
    ? state.GetTileView(actor->GetX(), actor->GetY())
    : state.GetTileView();

  // Draw all tiles in the view.
  for(const auto& tile : view.tiles){
    irr::core::position2d<irr::s32> topleft(
      origin.X + tile_size * tile.x,
      origin.Y - tile_size * tile.y);
    irr::core::rect<irr::s32> dest_rect(
      topleft.X, topleft.Y,
      topleft.X + tile_size, topleft.Y + tile_size);

    irr::core::rect<irr::s32> source_rect(0, 0, 16, 16);

    irr::video::ITexture* image = NULL;

    switch(tile.tile){
    case Tile::Stone:
      image = stone;
      break;
    case Tile::Dirt:
      image = dirt;
      break;
    case Tile::OutOfBounds:
      image = outofbounds;
      break;
    case Tile::Empty:
      image = empty;
      break;
    case Tile::Unseen:
      image = unseen;
      break;
    }

    if(image != NULL){
      driver->draw2DImage(image, dest_rect, source_rect,
                          NULL, NULL, true);
    }
  }

  // Draw all actors in the view
  for(auto& actor : view.actors){
    irr::core::position2d<irr::s32> topleft(
      origin.X + tile_size * actor.x,
      origin.Y - tile_size * actor.y);
    irr::core::rect<irr::s32> dest_rect(
      topleft.X, topleft.Y,
      topleft.X + tile_size, topleft.Y + tile_size);

    irr::core::rect<irr::s32> source_rect(0, 0, 16, 16);

    auto color = actor.color;

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
  }
  if(empty == NULL){
    empty = driver->getTexture("resources/empty.png");
  }
  if(unseen == NULL){
    unseen = driver->getTexture("resources/unseen.png");
  }
}

void GameStateRenderer::SetViewpoint(std::shared_ptr<const Actor> actor){
  viewed_from = actor;
}
