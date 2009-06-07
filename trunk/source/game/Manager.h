#ifndef MANAGER_H_
#define MANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

  const int N_ROWS(52);
  const int N_COLS(80);
  const int PLAYER_OFFSET(5);

  class Manager {
    private:
      App* app;
      Player* player1;
      Player* player2;
      Terrain* terrain;
      list<Ammo*>* ammosToDraw;
      void computeAmmosCollisions();
      void deleteAmmosToDraw();
      bool ammoIsOffScreen(const int screenX) const;
      bool ammoIsTooHigh(const int screenY) const;
      bool ammoHitTheGround(const int screenX, const int screenY) const;
      Ammo* ammoHitAnotherAmmo(Ammo*) const;
      Player* ammoHitAPlayer(Ammo*);
      
    public:
      Manager(App*, string nick_p1 = "Player 1", string nick_p2 = "Player 2");
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
      void drawAmmos();
      void show();
      void dealEvent(const u32*, const u32*);
      void addAmmosToDraw(Ammo*);
  };

}

#endif /*MANAGER_H_*/
