#include "../ShootMii.h"

namespace shootmii {

  GameScreen::GameScreen(App* _app, string nick_p1, string nick_p2) :
    Screen(_app), player1(new Player(nick_p1)), player2(new Player(nick_p2)), terrain(new Terrain(CELL_SIZE,N_ROWS,N_COLS)), score_panel(new ScorePanel(_app,player1,player2)),
        tex_screen(GRRLIB_LoadTexture(game_select_screen)) {
    // Initialisation de la position des joueurs
  }

  GameScreen::~GameScreen() {
    free(tex_screen.data);
    delete player1;
    delete player2;
    delete terrain;
    delete score_panel;
  }

  void GameScreen::draw() {
    /* Barre du bas */
    terrain->draw();
    score_panel->draw();
    player1->draw();
    player2->draw();
  }

  void GameScreen::show() {
    terrain->generate();
    initPlayerPosition(player1, PLAYER_OFFSET);
    initPlayerPosition(player2, N_COLS-PLAYER_OFFSET);
  }

  void GameScreen::dealEvent(const u32 pad1Down, const u32 pad2Down) {
    if(pad1Down & WPAD_BUTTON_LEFT) {
      moveLeft(player1);
    }
    if(pad1Down & WPAD_BUTTON_RIGHT) {
      moveRight(player1);
    }
    if(pad2Down & WPAD_BUTTON_LEFT) {
      moveLeft(player2);
    }
    if(pad2Down & WPAD_BUTTON_RIGHT) {
      moveRight(player2);
    }
  }

  void GameScreen::initPlayerPosition(Player* player, int colIndex) const {
    for (int rowIndex = 0; rowIndex < N_ROWS; rowIndex++) {
      if (terrain->getCellType(rowIndex, colIndex) == GRASS) {
        player->setCoords(rowIndex-1, colIndex);
        break;
      }
    }
  }
  
  void GameScreen::moveLeft(Player* player) {
    if(player->getColIndex() > 0) {
      initPlayerPosition(player, player->getColIndex() - 1);
    }
  }
  
  void GameScreen::moveRight(Player* player) {
    if(player->getColIndex() < N_COLS) {
      initPlayerPosition(player, player->getColIndex() + 1);
    }
  }
}
