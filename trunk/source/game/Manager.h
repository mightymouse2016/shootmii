#ifndef MANAGER_H_
#define MANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

  const int N_ROWS(52);
  const int N_COLS(80);
  const int PLAYER_OFFSET(5);

  class Manager {
    private:
      Player* player1;
      Player* player2;
      Terrain* terrain;
      list<Ammo*>* ammosToMove;
      list<Ammo*>* ammosToDestroy;
      void computeAmmosCollisions();
      void deleteAmmosToMove();
      void deleteAmmosToDestroy();
      
    public:
      Manager(string nick_p1 = "Player 1", string nick_p2 = "Player 2");
      ~Manager();
      // Accesseurs
      Player* getPlayer1();
      Player* getPlayer2();
      // Autres méthodes
      Player* opponent(Player*);
      void initPlayerPosition(Player* player, int offSet = 0) const;
      void moveLeft(Player*);
      void moveRight(Player*);
      void draw();
      void show();
      void dealEvent(const u32*, const u32*);
      void addAmmoToMove(Ammo*);
      void addAmmoToDestroy(Ammo*);
  };

}

#endif /*MANAGER_H_*/
