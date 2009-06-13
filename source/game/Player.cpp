#include "../ShootMii.h"

namespace shootmii {

  Player::Player(const string & _nickName, const float _angleOffSet,
    const float _angleRange, const float _angle, const float _rotationStep,
    const u8 _life, const bool _fury, Bonus _bonus) :
    nickName(_nickName), life(_life), fury(_fury), bonus(_bonus),
        cannon(new Cannon(_angleOffSet,_angleRange,_angle,_rotationStep)), nbGamesWon(0) {
  }

  void Player::init() {
    nbGamesWon = 0;
    initGame();
  }
  
  void Player::initGame() {
    life = 100;
    fury = false;
    bonus = NORMAL;
    cannon->init();
  }
  
  Cannon* Player::getCannon() {
    return cannon;
  }
  
  Cannon* Player::getCannon() const{
     return cannon;
  }

  void Player::draw() const {
    cannon->draw(screenX, screenY, CELL_SIZE);
    GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, YELLOW, true);
  }

  u8 Player::getLife() const {
    return life;
  }

  void Player::looseLife(u8 lifeAmount) {
    // Il est deja mort
    if(life == 0) return;
    // Il meurt
    if(lifeAmount >= life) {
      life = 0;
    } 
    // Il est toujours vivant
    else {
      life -= lifeAmount;
    }    
  }
  
}
