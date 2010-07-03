#include "../world/Wind.h"
#include "../world/World.h"
#include "../world/Terrain.h"
#include "../tools/Animation.h"
#include "../tools/Console.h"
#include "../App.h"
#include "JaugeManager.h"
#include "ScoreManager.h"
#include "DrawManager.h"
#include "Player.h"
#include "Bonus.h"
#include "Ammo.h"
#include "Manager.h"

namespace shootmii {

JaugeManager* Manager::jaugeManager = new JaugeManager;

Manager::Manager(App* _app) :
	pause(false),
	backFromPause(true),
	roundCount(DEFAULT_ROUND_COUNT),
	app(_app),
	world(new World),
	player1(new Player(world->getTerrain(),world->getWind(),1,0,PI/2,PI/4,ROTATION_STEP,100,false,this)),
	player2(new Player(world->getTerrain(),world->getWind(),2,-PI/2,0,-PI/4,ROTATION_STEP,100,false,this)),
	ammos(new std::list<Ammo*>),
	bonuses(new std::list<Bonus*>),
	animations(new std::list<Animation*>)
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
	delete jaugeManager;
}

void Manager::togglePause(){
	if (pause) backFromPause = true;
	pause = !pause;
}

bool Manager::isInPause() const{
	return pause;
}

unsigned int Manager::getRoundCount() const{
	return roundCount;
}

void Manager::setRoundCount(const unsigned int _roundCount){
	roundCount = _roundCount;
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
	player1->initRound();
	player2->initRound();
	player1->initPosition(PLAYER_OFFSET);
	player2->initPosition(world->getTerrain()->getCols()*world->getTerrain()->getCellWidth() - PLAYER_OFFSET);
}

void Manager::init(){
	pause = false;
	world->init();
	ammos->clear();
	bonuses->clear();
	animations->clear();
	jaugeManager->clear();
	initPlayers();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	if (backFromPause){
		backFromPause = false;
		return;
	}
	player1->dealEvent(player1Events);
	player2->dealEvent(player2Events);
}

void Manager::computeVictory() {
	Player* winner = NULL;
	if (player1->getLife() == 0) winner = player2;
	else if (player2->getLife() == 0) winner = player1;
	if (winner) {
		winner->incScore();
		if (winner->getScore() >= roundCount) {
			// TODO Rajouter la popup
			player1->initGame();
			player2->initGame();
		}
		init();
	}
}

void Manager::computeAnimations() {
	std::list<Animation*>* newAnimations = new std::list<Animation*>;
	for (std::list<Animation*>::iterator i=animations->begin();i!=animations->end();i++){
		if ((*i)->isFinished()) delete *i;
		else {
			(*i)->compute();
			newAnimations->push_back(*i);
		}
	}
	delete animations;
	animations = newAnimations;
}

void Manager::computeBonuses() {
	std::list<Bonus*>* newBonuses = new std::list<Bonus*>;
	for (std::list<Bonus*>::iterator i=bonuses->begin();i!=bonuses->end();i++){
		if ((*i)->isPossessed());	// Instruction vide : pas de push_back, le player prends le relai
		else if ((*i)->isFinished()) delete *i;
		else {
			(*i)->compute();
			newBonuses->push_back(*i);
		}
	}
	delete bonuses;
	bonuses = newBonuses;
}

void Manager::computeAmmos() {
	std::list<Ammo*>* newAmmos = new std::list<Ammo*> ;
	for (std::list<Ammo*>::iterator i=ammos->begin();i!=ammos->end();i++) {

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
		else if ((*i)->hitABonus(bonuses)) {
			App::console->addDebug("collision : bonus");
		}

		// Collision avec le bouclier du player 1
		else if ((*i)->hitAShield(player1)){
			App::console->addDebug("collision : player1's shield");
			addAnimation((*i)->destruction(HIT_A_SHIELD));
			(*i)->deleteMe();
		}

		// Collision avec le bouclier du player 2
		else if ((*i)->hitAShield(player2)){
			App::console->addDebug("collision : player2's shield");
			addAnimation((*i)->destruction(HIT_A_SHIELD));
			(*i)->deleteMe();
		}
	}

	//Boucle de suppression
	for (std::list<Ammo*>::iterator i=ammos->begin();i!=ammos->end();i++) {
		if ((*i)->isToDelete()) delete *i;
		else newAmmos->push_back(*i);
	}

	delete ammos;
	ammos = newAmmos;
}

void Manager::compute() {
	if (!(rand()%BONUS_PROBABILITY)) addBonus(randomBonus());
	jaugeManager->compute();
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
