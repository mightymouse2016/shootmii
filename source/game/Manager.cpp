#include "../ShootMii.h"

namespace shootmii {

  Manager::Manager(App* _app, string nick_p1, string nick_p2) :
        app(_app),
        player1(new Player(nick_p1,BLUE,0,ROTATION_RANGE,INIT_ANGLE,ROTATION_STEP)),
        player2(new Player(nick_p2,RED,ANGLE_OFFSET,ROTATION_RANGE,INIT_ANGLE+ANGLE_OFFSET,ROTATION_STEP)),
        world(new World),
        ammosToDraw(new list<Ammo*>){
  }

  Manager::~Manager() {
    delete player1;
    delete player2;
    delete world;
    // Destroy Ammos that are still in the air
    ammosToDraw->clear();
    delete ammosToDraw;
  }

  void Manager::addAmmosToDraw(Ammo* ammo) const{
    ammosToDraw->push_back(ammo);
  }

  Player* Manager::getPlayer1() const{
    return player1;
  }

  Player* Manager::getPlayer2() const{
    return player2;
  }

  Player* Manager::opponent(const Player* player) const{
    if (player == player1) return player2;
    else return player1;
  }

  void Manager::initPlayerPosition(Player* player, int colIndex) const{
    for (int rowIndex = 0; rowIndex < N_ROWS; rowIndex++)
      if (world->getTerrain()->getCellType(rowIndex, colIndex) == GRASS) {
        player->setCoords(rowIndex-1, colIndex);
        break;
      }
  }

  void Manager::moveLeft(Player* player) const{
    if (player->getColIndex()> 0) // On vérifie que l'on n'est pas à coté du bord
      if (player->getColIndex() != opponent(player)->getColIndex() + 1) // On vérifie que l'on n'est pas à coté d'un ennemi
        initPlayerPosition(player, player->getColIndex() - 1);
  }

  void Manager::moveRight(Player* player) const{
    if (player->getColIndex() < N_COLS)
      if (player->getColIndex() != opponent(player)->getColIndex() - 1)
        initPlayerPosition(player, player->getColIndex() + 1);
  }

  bool Manager::ammoIsOffScreen(const int screenX) const{
    return (screenX> SCREEN_WIDTH || screenX < 0);
  }

  bool Manager::ammoIsTooHigh(const int screenY) const{
    return (screenY < 0);
  }

  bool Manager::ammoHitTheGround(const int screenX, const int screenY) const{
    return (world->getTerrain()->getCellType(int(screenY)/CELL_SIZE, int(screenX)/CELL_SIZE) != SKY);
  }

  Ammo* Manager::ammoHitAnotherAmmo(const Ammo* ammo) const{
    list<Ammo*>::iterator it;
    for (it = ammosToDraw->begin(); it != ammosToDraw->end(); it++)
      if (ammo != *it && ammo->cellIntersect(*it)) return *it;
    return NULL;
  }

  Player* Manager::ammoHitAPlayer(const Ammo* ammo) const{
    if (ammo->cellIntersect(player1)) return player1;
    if (ammo->cellIntersect(player2)) return player2;
    return NULL;
  }

  void Manager::compute(){
    world->compute();
    player1->getCannon()->decHeat();
    player2->getCannon()->decHeat();
    computeAmmosCollisions();
    computeVictory();
  }
  
  void Manager::draw() const{
    world->drawBackground();
    drawAmmos();
    player1->draw();
    player2->draw();
    world->drawForeground();
  }
  
  void Manager::drawAmmos() const{
    for (list<Ammo*>::iterator i=ammosToDraw->begin();i!=ammosToDraw->end();i++)
      if (!((*i)->isBeingDestroyed())) (*i)->draw();
  }

  void Manager::computeVictory() {
    Player* winner = NULL;
    
    if (player1->getLife() == 0) winner = player2;
    else if (player2->getLife() == 0) winner = player1;
    
    if (winner) {
      winner->incScore();
      if (winner->getScore() >= MANCHE) {
        player1->setScore(0);
        player2->setScore(0);
      }
      startGame();
    }
  }

  void Manager::computeAmmosCollisions() {
    int screenX, screenY;
    list<Ammo*>* newAmmosToDraw = new list<Ammo*>;

    for (list<Ammo*>::iterator i=ammosToDraw->begin();i!=ammosToDraw->end();i++) {
      screenX = (*i)->getScreenX();
      screenY = (*i)->getScreenY();

      // Si la munition a déjà rencontré d'obstacle
      if ((*i)->isBeingDestroyed()) delete *i;

      else {
        // Si la munition sors de l'ecran sur X, suppression
        if (ammoIsOffScreen(screenX)) (*i)->destruction();
        // Si la munition est au dessus : on continue le calcul
        else if (ammoIsTooHigh(screenY)) newAmmosToDraw->push_back(*i);
        // Si la munition est sur l'ecran
        else if (world->getTerrain()->contains(screenX, screenY)) {
          // Gestion des collisions avec le terrain
          if (ammoHitTheGround(screenX, screenY)) (*i)->destruction();
          // Gestion des collisions avec les autres missiles
          else if (Ammo* inFrontAmmo = ammoHitAnotherAmmo(*i)) {
            app->getConsole()->addDebug("rencontre explosive!!!");
            (*i)->destruction();
            inFrontAmmo->destruction();
          }
          // TODO : Gestion des collisions avec les players
          else if (Player* playerHit = ammoHitAPlayer(*i)) {
            if (playerHit == player1) player1->looseLife(25);
            else player2->looseLife(25);
            (*i)->destruction();
          }
          // Sinon la munition se deplace
          else newAmmosToDraw->push_back(*i);
        }
        (*i)->updateXYT();
      }
    }
    delete ammosToDraw;
    ammosToDraw = newAmmosToDraw;
  }



  void Manager::show() const{
    player1->init();
    player2->init();
    startGame();
  }

  void Manager::startGame() const{
    world->getTerrain()->generate();
    initPlayers();
  }

  void Manager::initPlayers() const{
    initPlayerPosition(player1, PLAYER_OFFSET);
    initPlayerPosition(player2, N_COLS-PLAYER_OFFSET);
    player1->initGame();
    player2->initGame();
  }

  void Manager::dealEvent(const u32* player1Events, const u32* player2Events){
    const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
    const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];
    
    if (pad1Held & WPAD_BUTTON_LEFT) moveLeft(player1);
    if (pad1Held & WPAD_BUTTON_RIGHT) moveRight(player1);
    if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
    if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

    if (pad2Held & WPAD_BUTTON_LEFT) moveLeft(player2);
    if (pad2Held & WPAD_BUTTON_RIGHT) moveRight(player2);
    if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
    if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

    if (pad1Down & WPAD_BUTTON_A) {
      player1->getCannon()->shoot(this);
      WPAD_Rumble(WPAD_CHAN_0, 1);
      WPAD_Rumble(WPAD_CHAN_0, 0);
    }
  
    if (pad2Down & WPAD_BUTTON_A) {
      player2->getCannon()->shoot(this);
      WPAD_Rumble(WPAD_CHAN_1, 1);
      WPAD_Rumble(WPAD_CHAN_1, 0);
    }

  }

}
