#include "../tools/Console.h"
#include "../world/Terrain.h"
#include "../tools/Tools.h"
#include "../world/Wind.h"
#include "../math/PolyDeg2.h"
#include "../math/Coordinates.h"
#include "../App.h"
#include "Ammo.h"
#include "Cannon.h"
#include "Player.h"
#include "IA.h"

namespace shootmii{

IA::IA(Player* const _player) :
	player(_player),
	computedAngles(NULL),
	computedStrength(NULL),
	firing(false)
{

}

IA::~IA(){
	delete computedAngles;
	delete computedStrength;
}

void IA::init(){
	delete computedAngles;
	computedAngles = NULL;
	delete computedStrength;
	computedStrength = NULL;
	firing = false;
	player->KeyA(UP);
}

void IA::getCloserToTheOpponent(){
	if (player->getPlayerNumber() == 1) player->KeyRight(HELD);
	else player->KeyLeft(HELD);
}

void IA::drawDebug() const{
	const Coordinates origin = player->getCannon()->getAbsoluteOrigin();
	const float angle = player->getCannon()->getAbsoluteAngle();
	Interval range = player->getAngularInterval();

	// Force variable
	if (computedStrength) drawTrajectory(*computedStrength,origin,angle,Color::RED);

	// Angle variable
	if (computedAngles){
		drawTrajectory(100,origin,computedAngles->getMin()+PI/2,Color::GREEN);
		drawTrajectory(100,origin,computedAngles->getMax()+PI/2,Color::GREEN);
		drawTrajectory(100,origin,(computedAngles->getMin()+computedAngles->getMax())/2+PI/2,Color::WHITE);
	}

	// Min/Max
	drawTrajectory(100,origin,range.getMin()+PI/2,Color::BLUE);
	drawTrajectory(100,origin,range.getMax()+PI/2,Color::BLUE);
}

void IA::drawTrajectory(const float strength, const Coordinates& origin, const float angle, const Color color) const{
	Cannon* cannon = player->getCannon();
	Terrain* terrain = cannon->getOwner()->getTerrain();

	const float wind = cannon->getWind()->getWindSpeed();
	const float cosinus = cos(angle), sinus = sin(angle);
	float x = origin.getX(), y = origin.getY();
	float newX = x, newY = y;

	PolyDeg2 *laserX = new PolyDeg2(
			wind*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT),
			strength*cosinus,
			origin.getX()+CANNON_LENGTH*cosinus);

	PolyDeg2 *laserY = new PolyDeg2(
			-GRAVITY/(2*AMMO_WEIGHT),
			strength*sinus,
			origin.getY()+CANNON_LENGTH*sinus);

	for(int t = 0;newY<terrain->getHeight(newX);t++){
		GRRLIB_Line(x, y, newX, newY,color);
		x = newX;
		y = newY;
		newX = (*laserX)(t*LASER_STEP);
		newY = (*laserY)(t*LASER_STEP);
	}
}

void IA::compute(){
	const float angle = fixAngle(player->getCannon()->getAbsoluteAngle());
	Interval interval = player->getAngularInterval();

	delete computedAngles;
	computedAngles = calculateAngle(100);

	delete computedStrength;
	computedStrength = calculateStrength();

	/*********************************************************************************/
	/*                    Asservissement angulaire et positionnel                    */
	/*********************************************************************************/

	// Si on n'est pas à une distance permettant d'atteindre l'adversaire
	if (!computedAngles) getCloserToTheOpponent();
	else {
		// On se dirige vers l'angle optimal
		if (angle < (computedAngles->getMin()+computedAngles->getMax())/2) player->getCannon()->rotateRight();
		else player->getCannon()->rotateLeft();

		// Si dans la position ou l'on est, on ne peux atteindre l'enemi, on se rapproche de lui
		if (!interval.intersect(*computedAngles)) getCloserToTheOpponent();
	}

	/*********************************************************************************/
	/*                        Contrôle de la puissance de feu                        */
	/*********************************************************************************/

	if (player->getCannon()->isOverHeated()) return;

	// Si l'adversaire est ateignable
	if(computedStrength){
		// Si on est en train de tirer
		if (firing){
			// Si la puissance est insuffisante, on l'augmente
			if (player->getCannon()->getStrength() < *computedStrength) player->KeyA(HELD);
			// Sinon on tire
			else {
				firing = false;
				player->KeyA(UP);
			}
		}
		// Sinon on tire
		else{
			firing = true;
		}
	}
	// Sinon
	else{
		// Si on est en train de tirer, on continue pour éloigner l'explosion de soi ...
		if (firing) player->KeyA(HELD);
	}

}

float* IA::calculateStrength() const{
	const Coordinates originA = player->getCannon()->getAbsoluteOrigin();
	const Coordinates originB = player->getOpponent()->getCannon()->getAbsoluteOrigin();

	const float angle = player->getCannon()->getAbsolutePolygonAngle();
	const float cosinus = cos(angle);
	const float sinus = sin(angle);

	const float a1 = player->getCannon()->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT);
	const float dx = originB.getX() - originA.getX() - CANNON_LENGTH*cosinus;

	const float a2 = -GRAVITY/(2*AMMO_WEIGHT);
	const float dy = originB.getY() - originA.getY() - CANNON_LENGTH*sinus;

	const float s_square_bottom = (dy*cosinus-dx*sinus)*(a2*cosinus-a1*sinus);

	if (s_square_bottom <= 0) return NULL;

	return new float(fabs(a1*dy-a2*dx)/sqrt(s_square_bottom));
}

Interval* IA::calculateAngle(const float s) const{
	if (s == 0) return NULL;

	float dx = player->getOpponent()->getCannon()->getAbsoluteOriginX() - player->getCannon()->getAbsoluteOriginX();
	float dy = player->getOpponent()->getCannon()->getAbsoluteOriginY() - player->getCannon()->getAbsoluteOriginY();

	const float a1 = player->getCannon()->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT);
	const float a2 = -GRAVITY/(2*AMMO_WEIGHT);

	const float delta = s*s*s*s+4*((a1*dx+a2*dy)*s*s-pow(a1*dy-a2*dx,2));

	if (delta < 0) return NULL; // Aucune solution

	const float sqrt_delta = sqrt(delta);

	const float gamma1 = (s*s+2*(a1*dx+a2*dy)-sqrt_delta)/(2*(a1*a1+a2*a2));
	const float gamma2 = (s*s+2*(a1*dx+a2*dy)+sqrt_delta)/(2*(a1*a1+a2*a2));

	return new Interval(fixAngle(atan2(a2*gamma1-dy,a1*gamma1-dx)-PI),fixAngle(atan2(a2*gamma2-dy,a1*gamma2-dx)-PI));
}

bool IA::isCollidingWithOpponent(const float strength, float angle){
	Player* opponent = player->getOpponent();
	Cannon* cannon = player->getCannon();
	Terrain* terrain = cannon->getOwner()->getTerrain();

	const float wind = cannon->getWind()->getWindSpeed();
	const float cosinus = cos(angle), sinus = sin(angle);
	const float oX = cannon->getAbsoluteOriginX(), oY = cannon->getAbsoluteOriginY();
	float x = oX, y = oY, newX = oX, newY = oY;

	PolyDeg2 *laserX = new PolyDeg2(
			wind*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT),strength*cosinus,oX+CANNON_LENGTH*cosinus);
	PolyDeg2 *laserY = new PolyDeg2(
			-GRAVITY/(2*AMMO_WEIGHT),strength*sinus,oY+CANNON_LENGTH*sinus);

	for(int t = 0;newY<terrain->getHeight(newX);t++){
		if (opponent->intersect(Segment(x,y,newX,newY))) return true;
		x = newX;
		y = newY;
		newX = (*laserX)(t*LASER_STEP);
		newY = (*laserY)(t*LASER_STEP);
	}
	return false;
}

}
