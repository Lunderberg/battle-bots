#ifndef _GAMESTATERENDERER_H_
#define _GAMESTATERENDERER_H_

#include <memory>

#include <irrlicht.h>

class GameState;

class GameStateRenderer{
public:
  GameStateRenderer(std::shared_ptr<GameState> state);

  void Update(irr::IrrlichtDevice* device);
  void Draw(irr::video::IVideoDriver* driver);

  int GetTileSize(){ return tile_size; }
  void SetTileSize(int tile_size){ this->tile_size = tile_size; }

  double GetScrollSpeed(){ return scroll_speed; }
  void SetScrollSpeed(double scroll_speed){ this->scroll_speed = scroll_speed; }

private:
  void PanViewpoint(irr::IrrlichtDevice* device);

  std::shared_ptr<GameState> state;
  irr::video::ITexture* background;
  irr::video::ITexture* stone;
  irr::video::ITexture* dirt;
  irr::video::ITexture* outofbounds;

  irr::core::vector2df center;
  int tile_size;
  double scroll_speed;
};

#endif /* _GAMESTATERENDERER_H_ */
