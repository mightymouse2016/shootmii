#include "../ShootMii.h"

namespace shootmii {

Manager::Manager(App* _app) :
	app(_app),
	world(new World),
	player1(new Player(world->getTerrain(),world->getWind(),1,0,PI/2,PI/4,ROTATION_STEP,100,false,this)),
	player2(new Player(world->getTerrain(),world->getWind(),2,-PI/2,0,-PI/4,ROTATION_STEP,100,false,this)),
	draws(new list<Polygon*>),
	ammos(new list<Ammo*>),
	bonuses(new list<Bonus*>),
	smoklets(new list<Animation*>),
	explosions(new list<Animation*>)
{
	player1->setOpponent(player2);
	player2->setOpponent(player1);
}

Manager::~Manager() {
	ammos->clear();
	bonuses->clear();
	smoklets->clear();
	explosions->clear();
	delete player1;
	delete player2;
	delete world;
	delete ammos;
	delete bonuses;
	delete smoklets;
	delete explosions;
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

void Manager::addAmmo(Ammo* ammo) const {
	ammos->push_back(ammo);
}

void Manager::addBonus(Bonus* bonus) const {
	bonuses->push_back(bonus);
}

void Manager::addDraw(Polygon* polygon) const {
	draws->push_back(polygon);
}

void Manager::addSmoklet(Animation* animation) const {
	smoklets->push_back(animation);
}

void Manager::addExplosion(Animation* animation) const {
	explosions->push_back(animation);
}

void Manager::initPlayers() const {
	player1->initPosition(PLAYER_OFFSET);
	player2->initPosition(world->getTerrain()->getCols()*world->getTerrain()->getCellWidth() - PLAYER_OFFSET);
	player1->initGame();
	player2->initGame();
}

void Manager::init() const {
	ammos->clear();
	bonuses->clear();
	smoklets->clear();
	explosions->clear();
	world->init();
	player1->init();
	player2->init();
	initPlayers();
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

void Manager::computeAnimations() {
	// On peux faire une liste de pair<int,Polygon*> trié sur le type int (ou un map)
	list<Animation*>* newAnimations = new list<Animation*>;
	for (list<Animation*>::iterator i=smoklets->begin();i!=smoklets->end();i++){
		if ((*i)->isFinished()){
			delete *i;
		}
		else {
			(*i)->compute();
			newAnimations->push_back(*i);
		}
	}
	delete smoklets;
	smoklets = newAnimations;
	newAnimations = new list<Animation*>;
	for (list<Animation*>::iterator i=explosions->begin();i!=explosions->end();i++){
		if ((*i)->isFinished()){
			delete *i;
		}
		else {
			(*i)->compute();
			newAnimations->push_back(*i);
		}
	}
	delete explosions;
	explosions = newAnimations;
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
		bonuses->clear();
		ammos->clear();
		smoklets->clear();
		explosions->clear();
		world->init();
		initPlayers();
	}
}

void Manager::computeBonus() {
	list<Bonus*>* newBonuses = new list<Bonus*>;
	for (list<Bonus*>::iterator i=bonuses->begin();i!=bonuses->end();i++){
		if ((*i)->isFinished()){
			delete *i;
		}
		else {
			(*i)->compute();
			newBonuses->push_back(*i);
		}
	}
	delete bonuses;
	bonuses = newBonuses;
}

void Manager::computeAmmos() {
	list<Ammo*>* newAmmos = new list<Ammo*> ;
	for (list<Ammo*>::iterator i=ammos->begin();i!=ammos->end();i++) {
		// Mise à jour de la position de l'ammo
		(*i)->compute();
		// Le missile vient de rencontrer un autre missile qui a déjà géré la collision
		if ((*i)->isDestroyed()) {
			App::console->addDebug("collision : missile 2/2");
			addExplosion((*i)->destruction(HIT_ANOTHER_AMMO));
			delete *i;
		}
		// Le missile est trop bas
		else if ((*i)->isTooLow()) {
			App::console->addDebug("missile trop bas -> suppression");
			delete *i;
		}
		// Missile en dehors de l'ecran
		else if (!world->getTerrain()->contains((*i)->getAbsoluteOriginX(),(*i)->getAbsoluteOriginY())) {
			//App::console->addDebug("missile en dehors de l'ecran");
			newAmmos->push_back(*i);
		}
		// Le missile touche le sol : explosion
		else if ((*i)->hitTheGround(world->getTerrain())){
			App::console->addDebug("collision : sol");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			addExplosion((*i)->destruction(HIT_THE_GROUND));
			delete *i;
		}
		// Collision inter-missile
		else if (Ammo * inFrontAmmo = (*i)->hitAnotherAmmo(ammos)) {
			App::console->addDebug("collision : missile 1/2");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			addExplosion((*i)->destruction(HIT_ANOTHER_AMMO));
			delete *i;
			inFrontAmmo->destroy();
		}
		// Collision avec un player
		else if (Player * playerHit = (*i)->hitAPlayer(player1,player2)) {
			App::console->addDebug("collision : player");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			playerHit->looseLife(HIT_DAMAGE_BONUS); // Un petit bonus pour le touché
			addExplosion((*i)->destruction(HIT_A_PLAYER,playerHit));
			delete *i;
		}
		// Collision avec un bonus
		else if (pair<Player*,Bonus*>* result = (*i)->hitABonus(bonuses)) {
			App::console->addDebug("collision : bonus");

			// Gestion du type de bonus
			switch (result->second->getType()){
			case HOMING:
				App::console->addDebug("bonus : homing missile");
				result->first->getCannon()->loadHoming();
				break;
			case LIFE_RECOVERY:
				App::console->addDebug("bonus : life recovery");
				result->first->setLife(100);
				break;
			default:
				App::console->addDebug("bonus : type inconnu");
				break;
			}

			delete result; // On ne peux libérer la mémoire qu'ici ...
			newAmmos->push_back(*i);
		}
		// Il ne se passe encore rien
		else {
			newAmmos->push_back(*i);
		}
	}
	delete ammos;
	ammos = newAmmos;

}

void Manager::compute() {
	if (!(rand()%BONUS_PROBABILITY)) addBonus(randomBonus());
	world->compute();
	player1->getCannon()->decHeat();
	player2->getCannon()->decHeat();
	player1->computeRecoil();
	player2->computeRecoil();
	computeAmmos();
	computeBonus();
	computeAnimations();
	computeVictory();
}

void Manager::drawExplosions() const {
  for (list<Animation*>::iterator i=explosions->begin();i!=explosions->end();i++){
    if (!(*i)->isFinished()) (*i)->draw();
  }
}

void Manager::drawSmoklets() const {
  for (list<Animation*>::iterator i=smoklets->begin();i!=smoklets->end();i++){
    if (!(*i)->isFinished()) (*i)->draw();
  }
}

void Manager::drawBonus() const {
	for (list<Bonus*>::iterator i=bonuses->begin();i!=bonuses->end();i++){
	  (*i)->draw();
	}
}

void Manager::drawAmmos() const {
	for (list<Ammo*>::iterator i=ammos->begin();i!=ammos->end();i++){
	  (*i)->draw();
	}
}

void Manager::draw() const {
	for (list<Polygon*>::iterator i=draws->begin();i!=draws->end();i++) (*i)->draw();
	world->drawBackground();
	drawSmoklets();
	world->drawMiddleground();
	drawAmmos();
	player1->draw();
	player2->draw();
	drawExplosions();
	drawBonus();
	world->drawForeground();
}

}
