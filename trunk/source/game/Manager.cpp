#include "../ShootMii.h"

namespace shootmii {

Manager::Manager(App* _app) :
	app(_app),
	world(new World),

	player1(
		new Player(
			world->getTerrain(),
			world->getWind(),
			1,
			0,
			PI/2,
			PI/4,
			ROTATION_STEP)),

	player2(
		new Player(
			world->getTerrain(),
			world->getWind(),
			2,
			-PI/2,
			0,
			-PI/4,
			ROTATION_STEP)),

			ammosToDraw(new list<Ammo*>),
			explosionsToDraw(new list<Explosion*>)
{
	player1->setOpponent(player2);
	player2->setOpponent(player1);
}

Manager::~Manager() {
	delete player1;
	delete player2;
	delete world;
	// Destroy Ammos that are still in the air
	ammosToDraw->clear();
	delete ammosToDraw;
	explosionsToDraw->clear();
	delete explosionsToDraw;
}

void Manager::addAmmosToDraw(Ammo* ammo) const {
	ammosToDraw->push_back(ammo);
}

void Manager::addExplosionsToDraw(Explosion* explosion) const {
  explosionsToDraw->push_back(explosion);
}

Player* Manager::getPlayer1() const {
	return player1;
}

Player* Manager::getPlayer2() const {
	return player2;
}

void Manager::compute() {
	world->compute();
	player1->getCannon()->decHeat();
	player2->getCannon()->decHeat();
	computeAmmos();
	computeExplosions();
	computeVictory();
}

void Manager::draw() const {
	world->drawBackground();
	player1->draw();
	player2->draw();
  drawAmmos();
  drawExplosions();
	world->drawForeground();
}

void Manager::drawAmmos() const {
	for (list<Ammo*>::iterator i=ammosToDraw->begin();i!=ammosToDraw->end();i++){
	  (*i)->draw();
	}
}

void Manager::drawExplosions() const {
  for (list<Explosion*>::iterator i=explosionsToDraw->begin();i!=explosionsToDraw->end();i++){
    (*i)->draw();
  }
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
		ammosToDraw->clear();
		explosionsToDraw->clear();
		world->init();
		initPlayers();
	}
}

void Manager::computeAmmos() {
	list<Ammo*>* newAmmosToDraw = new list<Ammo*> ;
	for (list<Ammo*>::iterator i=ammosToDraw->begin();i!=ammosToDraw->end();i++) {
	  // Le missile vient de rencontrer un autre missile qui a déjà géré la collision
	  if ((*i)->isDestroyed()) {
      App::console->addDebug("missile détruit en l'air");
      addExplosionsToDraw((*i)->destruction(HIT_ANOTHER_AMMO));
      delete *i;
	  }
	  // Le missile est trop bas
	   else if ((*i)->isTooLow()) {
		   App::console->addDebug("missile est trop bas");
		  delete *i;
		}
	  // Missile en dehors de l'ecran
		else if (!world->getTerrain()->contains((*i)->getAbsoluteOriginX(),(*i)->getAbsoluteOriginY())) {
			App::console->addDebug("missile en dehors de l'ecran");
			newAmmosToDraw->push_back(*i);
			(*i)->compute();
		}
	  // Le missile touche le sol : explosion
		else if ((*i)->hitTheGround(world->getTerrain())){
			App::console->addDebug("missile touche le sol : explosion");
		  addExplosionsToDraw((*i)->destruction(HIT_THE_GROUND));
		  delete *i;
		}
	  // Collision inter-missile
		else if (Ammo * inFrontAmmo = (*i)->hitAnotherAmmo(ammosToDraw)) {
			App::console->addDebug("collision inter-missile");
		  addExplosionsToDraw((*i)->destruction(HIT_ANOTHER_AMMO));
		  delete *i;
		  inFrontAmmo->destroy();
		}
		// Collision avec un player
		else if (Player * playerHit = (*i)->hitAPlayer(player1,player2)) {
			App::console->addDebug("collision player");
		  addExplosionsToDraw((*i)->destruction(HIT_A_PLAYER));
		  delete *i;
			playerHit->looseLife(25);
		}
		// Il ne se passe encore rien
		else {
			newAmmosToDraw->push_back(*i);
			(*i)->compute();
		}
	}
	delete ammosToDraw;
	ammosToDraw = newAmmosToDraw;
}

void Manager::computeExplosions() {
  list<Explosion*>* newExplosionsToDraw = new list<Explosion*>;
  for (list<Explosion*>::iterator i=explosionsToDraw->begin();i!=explosionsToDraw->end();i++) {
    if ((*i)->isFinished()) {
      App::console->addDebug("explosion est finished ...");
      delete *i;
    }
    else {
        App::console->addDebug("explosion en cours ...");
        (*i)->compute();
        newExplosionsToDraw->push_back(*i);
      }
  }
  delete explosionsToDraw;
  explosionsToDraw = newExplosionsToDraw;
}

void Manager::init() const {
	ammosToDraw->clear();
	explosionsToDraw->clear();
	world->init();
	player1->init();
	player2->init();
	initPlayers();
}

void Manager::initPlayers() const {
	player1->initPosition(world->getTerrain(), PLAYER_OFFSET);
	player2->initPosition(world->getTerrain(), world->getTerrain()->getCols()*world->getTerrain()->getCellWidth() - PLAYER_OFFSET);
	player1->initGame();
	player2->initGame();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
	const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];
	const u32 pad1Up = player1Events[UP], pad2Up = player2Events[UP];

	if (pad1Held & WPAD_BUTTON_LEFT) player1->moveLeft(world->getTerrain());
	if (pad1Held & WPAD_BUTTON_RIGHT) player1->moveRight(world->getTerrain());
	if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
	if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

	if (pad2Held & WPAD_BUTTON_LEFT) player2->moveLeft(world->getTerrain());
	if (pad2Held & WPAD_BUTTON_RIGHT) player2->moveRight(world->getTerrain());
	if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
	if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

	if (pad1Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_0, 1);
	if (pad1Held & WPAD_BUTTON_A) {
		player1->getCannon()->incStrength(this);
		if (!player1->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_0, 0);
	}
	if (pad1Up & WPAD_BUTTON_A) {
		player1->getCannon()->up();
		player1->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_0, 0);
	}

	if (pad2Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_1, 1);
	if (pad2Held & WPAD_BUTTON_A) {
		player2->getCannon()->incStrength(this);
		if (!player2->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_1, 0);
	}
	if (pad2Up & WPAD_BUTTON_A) {
		player2->getCannon()->up();
		player2->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_1, 0);
	}
}

}
