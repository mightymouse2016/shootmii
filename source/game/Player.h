#ifndef PLAYER_H_
#define PLAYER_H_

#include "../ShootMii.h"

namespace shootmii {

  enum Bonus {
    NORMAL,
    FIRE,
    FREEZE,
  };

  class Player : public Cell{
    private:
      std::string nickName;
      int life; // 0 -> 100
      int strength; // 0 -> 100
      int heat; // 0 -> 100
      bool fury;
      Bonus bonus;
    public:
      Player(const string & _nickName = "Player",const int _life = 100,const int _strength = 0,
        const int _heat = 0,const int _fury = false, Bonus _bonus = NORMAL);
      void draw() const;
  };

}
#endif /*PLAYER_H_*/
