#ifndef _GAMESTATERENDERER_H_
#define _GAMESTATERENDERER_H_

#include <algorithm>
#include <memory>

#include <irrlicht.h>

class GameState;

class GameStateRenderer{
public:


  GameStateRenderer(const GameState& state);

  void Draw(irr::video::IVideoDriver* driver, const GameState& state);

  int GetTileSize(){ return tile_size; }
  void SetTileSize(int tile_size){ this->tile_size = std::max(1, tile_size); }

  double GetScrollSpeed(){ return scroll_speed; }
  void SetScrollSpeed(double scroll_speed){ this->scroll_speed = scroll_speed; }

  irr::core::vector2df GetCenter(){ return center; }
  void SetCenter(irr::core::vector2df center){ this->center = center; }

private:
  void InitializeTextures(irr::video::IVideoDriver* driver);

  irr::video::ITexture* background;
  irr::video::ITexture* stone;
  irr::video::ITexture* dirt;
  irr::video::ITexture* outofbounds;
  irr::video::ITexture* actor_texture;
  irr::video::ITexture* empty;


  int tile_size;
  double scroll_speed;
  irr::core::vector2df center;
};

#endif /* _GAMESTATERENDERER_H_ */
