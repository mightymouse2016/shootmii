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
			ROTATION_STEP,
			100,
			false,
			this)),

	player2(
		new Player(
			world->getTerrain(),
			world->getWind(),
			2,
			-PI/2,
			0,
			-PI/4,
			ROTATION_STEP,
			100,
			false,
			this)),

			ammosToDraw(new list<Ammo*>),
			explosionsToDraw(new list<Explosion*>),
			animationsToDraw(new list<Animation*>)
{
	player1->setOpponent(player2);
	player2->setOpponent(player1);
}

Manager::~Manager() {
	delete player1;
	delete player2;
	delete world;
	ammosToDraw->clear();
	delete ammosToDraw;
	explosionsToDraw->clear();
	delete explosionsToDraw;
	animationsToDraw->clear();
	delete animationsToDraw;
}

void Manager::addAmmosToDraw(Ammo* ammo) const {
	ammosToDraw->push_back(ammo);
}

void Manager::addExplosionsToDraw(Explosion* explosion) const {
	explosionsToDraw->push_back(explosion);
}

void Manager::addAnimationsToDraw(Animation* animation) const {
	animationsToDraw->push_back(animation);
}

Player* Manager::getPlayer1() const {
	return player1;
}

Player* Manager::getPlayer2() const {
	return player2;
}

Wind* Manager::getWind() const{
	return world->getWind();
}

void Manager::compute() {
	world->compute();
	player1->getCannon()->decHeat();
	player2->getCannon()->decHeat();
	player1->computeRecoil();
	player2->computeRecoil();
	computeAmmos();
	computeExplosions();
	computeAnimations();
	computeVictory();
}

void Manager::draw() const {
	world->drawBackground();
	player1->draw();
	player2->draw();
	drawAnimations();
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

void Manager::drawAnimations() const {
  for (list<Animation*>::iterator i=animationsToDraw->begin();i!=animationsToDraw->end();i++){
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
  		player1->computeDamage(*i);
  		player2->computeDamage(*i);
  	  addExplosionsToDraw((*i)->destruction(HIT_THE_GROUND));
  	  delete *i;
  	}
    // Collision inter-missile
  	else if (Ammo * inFrontAmmo = (*i)->hitAnotherAmmo(ammosToDraw)) {
  		App::console->addDebug("collision inter-missile");
  		player1->computeDamage(*i);
  		player2->computeDamage(*i);
  	  addExplosionsToDraw((*i)->destruction(HIT_ANOTHER_AMMO));
  	  delete *i;
  	  inFrontAmmo->destroy();
  	}
  	// Collision avec un player
  	else if (Player * playerHit = (*i)->hitAPlayer(player1,player2)) {
  		App::console->addDebug("collision player");
  		player1->computeDamage(*i);
  		player2->computeDamage(*i);
  		playerHit->looseLife(HIT_DAMAGE_BONUS); // Un petit bonus pour le touché
  		addExplosionsToDraw((*i)->destruction(HIT_A_PLAYER));
  		delete *i;
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
      App::console->addDebug("explosion finie");
      delete *i;
    }
    else {
        (*i)->compute();
        newExplosionsToDraw->push_back(*i);
      }
  }
  delete explosionsToDraw;
  explosionsToDraw = newExplosionsToDraw;
}

void Manager::computeAnimations() {
	list<Animation*>* newAnimationsToDraw = new list<Animation*>;
	for (list<Animation*>::iterator i=animationsToDraw->begin();i!=animationsToDraw->end();i++){
		if ((*i)->isFinished()){
			App::console->addDebug("animation finie");
			delete *i;
		}
		else {
			(*i)->compute();
			newAnimationsToDraw->push_back(*i);
		}
	}
	delete animationsToDraw;
	animationsToDraw = newAnimationsToDraw;
}

void Manager::init() const {
	ammosToDraw->clear();
	explosionsToDraw->clear();
	animationsToDraw->clear();
	world->init();
	player1->init();
	player2->init();
	initPlayers();
}

void Manager::initPlayers() const {
	player1->initPosition(PLAYER_OFFSET);
	player2->initPosition(world->getTerrain()->getCols()*world->getTerrain()->getCellWidth() - PLAYER_OFFSET);
	player1->initGame();
	player2->initGame();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
	const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];
	const u32 pad1Up = player1Events[UP], pad2Up = player2Events[UP];

	if (pad1Held & WPAD_BUTTON_LEFT) player1->moveLeft();
	if (pad1Held & WPAD_BUTTON_RIGHT) player1->moveRight();
	if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
	if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

	if (pad2Held & WPAD_BUTTON_LEFT) player2->moveLeft();
	if (pad2Held & WPAD_BUTTON_RIGHT) player2->moveRight();
	if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
	if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

	if (pad1Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_0, 1);
	if (pad1Held & WPAD_BUTTON_A) {
		player1->getCannon()->incStrength();
		if (!player1->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_0, 0);
	}
	if (pad1Up & WPAD_BUTTON_A) {
		player1->getCannon()->up();
		player1->getCannon()->shoot();
		WPAD_Rumble(WPAD_CHAN_0, 0);
	}

	if (pad2Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_1, 1);
	if (pad2Held & WPAD_BUTTON_A) {
		player2->getCannon()->incStrength();
		if (!player2->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_1, 0);
	}
	if (pad2Up & WPAD_BUTTON_A) {
		player2->getCannon()->up();
		player2->getCannon()->shoot();
		WPAD_Rumble(WPAD_CHAN_1, 0);
	}
}

}
