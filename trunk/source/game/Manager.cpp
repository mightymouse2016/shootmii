#include "../ShootMii.h"

namespace shootmii {

  Manager::Manager(string nick_p1, string nick_p2) :
        player1(new Player(nick_p1,0,ROTATION_RANGE,INIT_ANGLE,ROTATION_STEP)),
        player2(new Player(nick_p2,ANGLE_OFFSET,ROTATION_RANGE,INIT_ANGLE+ANGLE_OFFSET,ROTATION_STEP)),
        terrain(new Terrain(CELL_SIZE,N_ROWS,N_COLS)),ammosToMove(new list<Ammo*>),ammosToDestroy(new list<Ammo*>) {
  }

  Manager::~Manager() {
    delete player1;
    delete player2;
    delete terrain;

    // Destroy Ammos that are still in the air
    deleteAmmosToMove();
    delete ammosToMove;
    
    // Destroy Ammos that are still self-destroying
    deleteAmmosToDestroy();
    delete ammosToDestroy;
  }

  void Manager::addAmmoToMove(Ammo* ammo) {
    ammosToMove->push_back(ammo);
  }

  void Manager::addAmmoToDestroy(Ammo* ammo) {
    ammosToDestroy->push_back(ammo);
  }
  
  void Manager::deleteAmmosToMove() {
    list<Ammo*>::iterator it;
    for (it = ammosToMove->begin(); it != ammosToMove->end(); it++)
      delete (*it);
  }
  
  void Manager::deleteAmmosToDestroy() {
    list<Ammo*>::iterator it;
    for (it = ammosToDestroy->begin(); it != ammosToDestroy->end(); it++)
      delete (*it);
  }
  
  Player* Manager::getPlayer1() {
    return player1;
  }

  Player* Manager::getPlayer2() {
    return player2;
  }

  Player* Manager::opponent(Player* player) {
    if (player == player1)
      return player2;
    else
      return player1;
  }

  void Manager::initPlayerPosition(Player* player, int colIndex) const {
    for (int rowIndex = 0; rowIndex < N_ROWS; rowIndex++)
      if (terrain->getCellType(rowIndex, colIndex) == GRASS) {
        player->setCoords(rowIndex-1, colIndex);
        break;
      }
  }

  void Manager::moveLeft(Player* player) {
    if (player->getColIndex() > 0) // On vérifie que l'on n'est pas à coté du bord
      if (player->getColIndex() != opponent(player)->getColIndex() + 1) // On vérifie que l'on n'est pas à coté d'un ennemi
        initPlayerPosition(player, player->getColIndex() - 1);
  }

  void Manager::moveRight(Player* player) {
    if (player->getColIndex() < N_COLS)
      if (player->getColIndex() != opponent(player)->getColIndex() - 1)
        initPlayerPosition(player, player->getColIndex() + 1);
  }

  void Manager::draw() {
    terrain->draw();
    player1->draw();
    player2->draw();

    computeAmmosCollisions();    
  }

  void Manager::computeAmmosCollisions() {
    int screenX;
        int screenY;
        list<Ammo*>* newAmmosToMove = new list<Ammo*>;
        list<Ammo*>::iterator it;
        
        for (it = ammosToMove->begin(); it != ammosToMove->end(); it++) {
          screenX = (*(*it)->getCalcX())((*it)->getT());
          screenY = (*(*it)->getCalcY())((*it)->getT());

          // Si la munition sors de l'ecran sur X
          // Suppression des éléments en dehors du terrain
          if (screenX > SCREEN_WIDTH || screenX < 0) {
            delete *it;
          }
          // Si la munition est au dessus : on continue le calcul mais on ne dessine rien : ca sert a rien
          else if(screenY < 0) {
            (*it)->incT();
            newAmmosToMove->push_back(*it);
          }
          // Si la munition est sur l'ecran
          else if (terrain->contains(screenX,screenY)) {
            // Gestion des collisions avec le terrain
            if(terrain->getCellType(int(screenY)/CELL_SIZE, int(screenX)/CELL_SIZE) != SKY) {
              addAmmoToDestroy(*it);
            }
            // TODO : Gestion des collisions avec les autres missiles
            
            // TODO : Gestion des collisions avec les players
            
            // Sinon la munition se deplace
            else {
              (*it)->draw();
              (*it)->incT();
              newAmmosToMove->push_back(*it);
            }
          }
        }
        delete ammosToMove;
        ammosToMove = newAmmosToMove;    
  }
  
  void Manager::show() {
    // On regenere un nouveau terrain
    terrain->generate();
    // On replace les joueurs 
    initPlayerPosition(player1, PLAYER_OFFSET);
    initPlayerPosition(player2, N_COLS-PLAYER_OFFSET);
    // On supprime les bombes de l'ecran
    deleteAmmosToMove();
    deleteAmmosToDestroy();
  }

  void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
    const u32 pad1Held = player1Events[HELD];
    if (pad1Held & WPAD_BUTTON_LEFT)
      moveLeft(player1);
    if (pad1Held & WPAD_BUTTON_RIGHT)
      moveRight(player1);
    if (pad1Held & WPAD_BUTTON_UP)
      player1->getCannon()->rotateLeft();
    if (pad1Held & WPAD_BUTTON_DOWN)
      player1->getCannon()->rotateRight();

    const u32 pad1Down = player1Events[DOWN];
    if (pad1Down & WPAD_BUTTON_A) {
      player1->getCannon()->shoot(this);
      WPAD_Rumble(WPAD_CHAN_0, 1);
      WPAD_Rumble(WPAD_CHAN_0, 0);
    }

    const u32 pad2Held = player2Events[HELD];
    if (pad2Held & WPAD_BUTTON_LEFT)
      moveLeft(player2);
    if (pad2Held & WPAD_BUTTON_RIGHT)
      moveRight(player2);
    if (pad2Held & WPAD_BUTTON_UP)
      player2->getCannon()->rotateRight();
    if (pad2Held & WPAD_BUTTON_DOWN)
      player2->getCannon()->rotateLeft();

    const u32 pad2Down = player2Events[DOWN];
    if (pad2Down & WPAD_BUTTON_A) {
      player2->getCannon()->shoot(this);
      WPAD_Rumble(WPAD_CHAN_1, 1);
      WPAD_Rumble(WPAD_CHAN_1, 0);
    }

  }

}
