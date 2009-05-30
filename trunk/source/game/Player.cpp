#include "../ShootMii.h"

namespace shootmii {
  
  Player::Player(const std::string & _nickName, const int _life,
    const int _strength, const int _heat, const int _fury, Bonus _bonus) :
    nickName(_nickName), life(_life), strength(_strength), heat(_heat),
        fury(_fury), bonus(_bonus) {
  }
  
  void Player::draw() const{
    GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, YELLOW, true);
  }
}
