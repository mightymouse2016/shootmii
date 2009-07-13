#include "../ShootMii.h"

namespace shootmii {

  Explosion::Explosion(GRRLIB_texImg* _tiles, const float _screenX,
    const float _screenY, const int _width, const int _height,
    const int _depth, const int _duration) :
    tiles(_tiles), screenX(_screenX), screenY(_screenY), width(_width),
        height(_height), depth(_depth), duration(_duration), t(-1) {
    GRRLIB_InitTileSet(tiles, width, height, 0);
  }

  Explosion::~Explosion() {
    // NOTHING TO DO
  }

  void Explosion::draw() {
    GRRLIB_DrawTile(//screenX, screenY,
        screenX-width/2,
        screenY-height+depth,
        *tiles, 0, 1, 1, WHITE, t);
  }

  void Explosion::compute() {
    t++;
  }

  bool Explosion::isFinished() {
      return (t == duration);
  }
}
