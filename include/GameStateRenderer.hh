#ifndef _GAMESTATERENDERER_H_
#define _GAMESTATERENDERER_H_

#include <memory>

class GameState;
namespace irr{
  namespace video{
    class IVideoDriver;
    class ITexture;
  }
}

class GameStateRenderer{
public:
  GameStateRenderer(std::shared_ptr<GameState> state);
  void Draw(irr::video::IVideoDriver* driver);

private:
  std::shared_ptr<GameState> state;
  irr::video::ITexture* background;
  irr::video::ITexture* stone;
  irr::video::ITexture* dirt;
};

#endif /* _GAMESTATERENDERER_H_ */
