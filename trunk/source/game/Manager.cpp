#include "../ShootMii.h"

namespace shootmii {

Manager::Manager(App* _app) :
	app(_app),
	world(new World),
	player1(new Player(world->getTerrain(),world->getWind(),1,0,PI/2,PI/4,ROTATION_STEP,100,false,this)),
	player2(new Player(world->getTerrain(),world->getWind(),2,-PI/2,0,-PI/4,ROTATION_STEP,100,false,this)),
	ammos(new list<Ammo*>),
	bonuses(new list<Bonus*>),
	animations(new list<Animation*>)
{
	player1->setOpponent(player2);
	player2->setOpponent(player1);
}

Manager::~Manager() {
	ammos->clear();
	bonuses->clear();
	animations->clear();
	delete ammos;
	delete bonuses;
	delete animations;
	delete player1;
	delete player2;
	delete world;
}

Player* Manager::getPlayer1() const {
	return player1;
}

Player* Manager::getPlayer2() const {
	return player2;
}

Wind* Manager::getWind() const {
	return world->getWind();
}

void Manager::addAmmo(Ammo* ammo) const {
	ammos->push_back(ammo);
}

void Manager::addBonus(Bonus* bonus) const {
	bonuses->push_back(bonus);
}

void Manager::addAnimation(Animation* animation) const {
	animations->push_back(animation);
}

void Manager::initPlayers() const {
	player1->init();
	player2->init();
	player1->initGame();
	player2->initGame();
	player1->initPosition(PLAYER_OFFSET);
	player2->initPosition(world->getTerrain()->getCols()*world->getTerrain()->getCellWidth() - PLAYER_OFFSET);
}

void Manager::init() const {
	world->init();
	ammos->clear();
	bonuses->clear();
	animations->clear();
	App::jaugeManager->clear();
	initPlayers();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
	const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];
	const u32 pad1Up = player1Events[UP], pad2Up = player2Events[UP];

	// Haut, bas, gauche, droite pour le joueur 1
	if (pad1Held & WPAD_BUTTON_LEFT) {
		if (player1->getCannon()->isGuidingMissile()) player1->getCannon()->getGuidedMissile()->rotateLeft();
		else player1->moveLeft();
	}
	if (pad1Held & WPAD_BUTTON_RIGHT) {
		if (player1->getCannon()->isGuidingMissile()) player1->getCannon()->getGuidedMissile()->rotateRight();
		else player1->moveRight();
	}
	if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
	if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

	// Haut, bas, gauche, droite pour le joueur 2
	if (pad2Held & WPAD_BUTTON_LEFT) {
		if (player2->getCannon()->isGuidingMissile()) player2->getCannon()->getGuidedMissile()->rotateLeft();
		else player2->moveLeft();
	}
	if (pad2Held & WPAD_BUTTON_RIGHT) {
		if (player2->getCannon()->isGuidingMissile()) player2->getCannon()->getGuidedMissile()->rotateRight();
		else player2->moveRight();
	}
	if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
	if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

	// A pressé, relaché, maintenu pour le joueur 1
	if (pad1Down & WPAD_BUTTON_A) {
		if (player1->getCannon()->isGuidingMissile()) player1->getCannon()->destroyGuidedMissile();
		//WPAD_Rumble(WPAD_CHAN_0, 1);
	}
	if (pad1Held & WPAD_BUTTON_A) {
		player1->getCannon()->incStrength();
		// TODO VibrationManager
		// Pour l'instant ca vide un peu trop les batteries ...
		//if (!player1->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_0, 0);
	}
	if (pad1Up & WPAD_BUTTON_A) {
		player1->getCannon()->up();
		player1->getCannon()->shoot();
		
		//MP3Player_PlayBuffer(Artillaryexp, Artillaryexp_size, NULL);
		ASND_SetVoice(0, VOICE_STEREO_16BIT, 22050, 0, (void*)Artillaryexp, Artillaryexp_size, MAX_VOLUME, MAX_VOLUME, NULL);
		//WPAD_Rumble(WPAD_CHAN_0, 0);
	}

	// A pressé, relaché, maintenu pour le joueur 2
	if (pad2Down & WPAD_BUTTON_A) {
		if (player2->getCannon()->isGuidingMissile()) player2->getCannon()->destroyGuidedMissile();
		//WPAD_Rumble(WPAD_CHAN_1, 1)
	}
	if (pad2Held & WPAD_BUTTON_A) {
		player2->getCannon()->incStrength();
		//if (!player2->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_1, 0);
	}
	if (pad2Up & WPAD_BUTTON_A) {
		player2->getCannon()->up();
		player2->getCannon()->shoot();
		//WPAD_Rumble(WPAD_CHAN_1, 0);
	}


	// B j1
	if (pad1Down & WPAD_BUTTON_B) {
		player1->useBonus();
	}
	// B j2
	if (pad2Down & WPAD_BUTTON_B) {
		player2->useBonus();
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
			player1->setFury(0);
			player2->setFury(0);
		}
		App::jaugeManager->clear();
		animations->clear();
		bonuses->clear();
		ammos->clear();
		world->init();
		initPlayers();
	}
}

void Manager::computeAnimations() {
	list<Animation*>* newAnimations = new list<Animation*>;
	for (list<Animation*>::iterator i=animations->begin();i!=animations->end();i++){
		if ((*i)->isFinished()){
			delete *i;
		}
		else {
			(*i)->compute();
			newAnimations->push_back(*i);
		}
	}
	delete animations;
	animations = newAnimations;
}

void Manager::computeBonuses() {
	list<Bonus*>* newBonuses = new list<Bonus*>;
	for (list<Bonus*>::iterator i=bonuses->begin();i!=bonuses->end();i++){
		if ((*i)->isFinished()) delete *i;
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
			App::console->addDebug("collision : destruction programmee");
			addAnimation((*i)->destruction(HIT_ANOTHER_AMMO));
			(*i)->deleteMe();
		}

		// Le missile est trop bas
		else if ((*i)->isTooLow()) {
			App::console->addDebug("missile trop bas -> suppression");
			(*i)->deleteMe();
		}

		// Missile en dehors de l'ecran
		else if (!(world->getTerrain()->contains((*i)->getAbsoluteOriginX(),(*i)->getAbsoluteOriginY())))
		{
			// NOTHING TO DO
		}

		// Le missile touche le sol : explosion
		else if ((*i)->hitTheGround(world->getTerrain())){
			App::console->addDebug("collision : sol");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			addAnimation((*i)->destruction(HIT_THE_GROUND));
			(*i)->deleteMe();
		}

		// Collision inter-missile
		else if (Ammo * inFrontAmmo = (*i)->hitAnotherAmmo(ammos)) {
			App::console->addDebug("collision : missile");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			addAnimation((*i)->destruction(HIT_ANOTHER_AMMO));
			(*i)->deleteMe();
			inFrontAmmo->destroy();
		}

		// Collision avec un player
		else if (Player * playerHit = (*i)->hitAPlayer(player1,player2)) {
			App::console->addDebug("collision : player");
			player1->computeDamage(*i);
			player2->computeDamage(*i);
			playerHit->loseLife(HIT_DAMAGE_BONUS); // Un petit bonus pour le touché
			if (playerHit == player1 && (*i)->getOwner() == player2) player2->winFury(10); //Un petit bonus de fury celui qui a réussi ce coup
			else if (playerHit == player2 && (*i)->getOwner() == player1) player1->winFury(10);
			addAnimation((*i)->destruction(HIT_A_PLAYER,playerHit));
			(*i)->deleteMe();
		}

		// Collision avec un bonus
		else if (pair<Player*,Bonus*>* result = (*i)->hitABonus(bonuses)) {
			App::console->addDebug("collision : bonus");
			// Ici on fait attention à gérer le cas improbable ou 2 munitions toucheraient le bonus à la même frame
			if (!result->second->isPossessed()) result->first->addBonus(result->second);

			// TODO enlever ca
			result->second = NULL;

			delete result;
		}
	}

	//Boucle de suppression
	for (list<Ammo*>::iterator i=ammos->begin();i!=ammos->end();i++) {
		if ((*i)->isToDelete()) delete *i;
		else newAmmos->push_back(*i);
	}

	delete ammos;
	ammos = newAmmos;
}

void Manager::compute() {
	if (!(rand()%BONUS_PROBABILITY)) addBonus(randomBonus());
	App::jaugeManager->compute();
	world->compute();
	player1->compute();
	player2->compute();
	computeAmmos();
	computeBonuses();
	computeVictory();
	computeAnimations();

}

void Manager::addToDrawManager() const {
	world->addToDrawManager();
	player1->addToDrawManager();
	player2->addToDrawManager();
	App::drawManager->addToDraw(ammos);
	App::drawManager->addToDraw(bonuses);
	App::drawManager->addToDraw(animations);
}

}
