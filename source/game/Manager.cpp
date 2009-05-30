#include "../ShootMii.h"

namespace shootmii {

  Manager::Manager(string nick_p1, string nick_p2) :
    player1(new Player(nick_p1,0,ROTATION_RANGE,INIT_ANGLE,ROTATION_STEP)),
        player2(new Player(nick_p2,ANGLE_OFFSET,ROTATION_RANGE,INIT_ANGLE+ANGLE_OFFSET,ROTATION_STEP)),
        terrain(new Terrain(CELL_SIZE,N_ROWS,N_COLS)) {
  }

  Manager::~Manager() {
    delete player1;
    delete player2;
    delete terrain;
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
  }

  void Manager::show() {
    terrain->generate();
    initPlayerPosition(player1, PLAYER_OFFSET);
    initPlayerPosition(player2, N_COLS-PLAYER_OFFSET);
  }

  void Manager::dealEvent(const u32 pad1Held, const u32 pad2Held) {
    if (pad1Held & WPAD_BUTTON_LEFT)
      moveLeft(player1);
    if (pad1Held & WPAD_BUTTON_RIGHT)
      moveRight(player1);
    if (pad1Held & WPAD_BUTTON_UP)
      player1->getCannon()->rotateLeft();
    if (pad1Held & WPAD_BUTTON_DOWN)
      player1->getCannon()->rotateRight();

    if (pad2Held & WPAD_BUTTON_LEFT)
      moveLeft(player2);
    if (pad2Held & WPAD_BUTTON_RIGHT)
      moveRight(player2);
    if (pad2Held & WPAD_BUTTON_UP)
      player2->getCannon()->rotateRight();
    if (pad2Held & WPAD_BUTTON_DOWN)
      player2->getCannon()->rotateLeft();
  }

}
