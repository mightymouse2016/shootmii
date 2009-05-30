#include "../ShootMii.h"

namespace shootmii {

  Player::Player(const string & _nickName, const float _angleOffSet,
    const float _angleRange, const float _angle, const float _rotationStep,
    const int _life, const int _strength, const int _heat, const int _fury,
    Bonus _bonus) :
    nickName(_nickName), life(_life), strength(_strength), heat(_heat),
        fury(_fury), bonus(_bonus), cannon(new Cannon(_angleOffSet,_angleRange,_angle,_rotationStep)) {
  }

  Cannon* Player::getCannon() {
    return cannon;
  }

  void Player::draw() const {
    cannon->draw(screenX, screenY, CELL_SIZE);
    GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, YELLOW, true);
  }
}
