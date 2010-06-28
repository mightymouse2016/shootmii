#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(
	const float _angle,
	GRRLIB_texImg* _image,
	PolyDeg2* _calcX,
	PolyDeg2* _calcY,
	Player* _owner,
	Terrain* _terrain,
	Manager* _manager):
		Polygon(AMMO_LAYER,TANK_HEIGHT/4, 0, AMMO_OVERTAKE, _angle, 0, true, true, _owner, Coordinates(-AMMO_WIDTH/2,-AMMO_HEIGHT/2), _image),
		Timer(TIME_BETWEEN_TWO_SMOKLET),
		calcX(_calcX),
		calcY(_calcY),
		destroyed(false),
		outOfCannon(false),
		outOfShield(false),
		fired(false),
		explosionFinished(false),
		terrain(_terrain),
		owner(_owner),
		manager(_manager),
		toDelete(false)
{
	GRRLIB_texImg* bubble;
	if (owner->getPlayerNumber() == 1) bubble = App::imageBank->get(TXT_GHOST1);
	else bubble = App::imageBank->get(TXT_GHOST2);

	children.push_back(new Rectangle(GHOST_LAYER,GHOST_WIDTH,GHOST_HEIGHT,0,0,0,0,0,true,true,bubble));
	getGhostBubble()->addChild(new Rectangle(GHOST_LAYER,AMMO_WIDTH,AMMO_HEIGHT,GHOST_OFFSET_X,0,0,0,0,true,true,_image));
	getGhostBubble()->hide();
	getGhostAmmo()->hide();
}

Ammo::~Ammo(){
	vertices.clear();
	delete calcX;
	delete calcY;
}

PolyDeg2* Ammo::getCalcX(){
	return calcX;
}

PolyDeg2* Ammo::getCalcY(){
	return calcY;
}

int Ammo::getCol() const {
	return originX/terrain->getCellWidth();
}

int Ammo::getRow() const {
	return originY/terrain->getCellHeight();
}

Rectangle* Ammo::getGhostAmmo() {
	return static_cast<Rectangle*>(getGhostBubble()->getChildren()[0]);
}

Rectangle* Ammo::getGhostAmmo() const {
	return static_cast<Rectangle*>(getGhostBubble()->getChildren()[0]);
}

Rectangle* Ammo::getGhostBubble() {
	return static_cast<Rectangle*>(children[CHILD_GHOST_BUBBLE]);
}

Rectangle* Ammo::getGhostBubble() const {
	return static_cast<Rectangle*>(children[CHILD_GHOST_BUBBLE]);
}

Player* Ammo::getOwner(){
	return owner;
}

void Ammo::computeOut(){
	if (!isOutOfCannon()) if (!intersect(owner)) outCannon();
}

Player* Ammo::getOwner() const{
	return owner;
}

void Ammo::computeGhost(){
	float ratio1, ratio2;
	Rectangle* ghostAmmo = getGhostAmmo();
	Rectangle* ghostBubble = getGhostBubble();

	/* Calcul des coordonnées (X,Y) de la bulle */
	// A gauche de l'écran
	if (originX < GHOST_MARGIN){
		ghostBubble->setOriginX(GHOST_MARGIN);	// Saturation des X
		if (originX > - GHOST_DISTANCE+GHOST_MARGIN) ratio1 = (-originX+GHOST_MARGIN)/GHOST_DISTANCE;
		else ratio1 = 1;
	}
	// A droite de l'écran
	else if (originX > SCREEN_WIDTH - GHOST_MARGIN){
		ghostBubble->setOriginX(SCREEN_WIDTH - GHOST_MARGIN); // Saturation X
		if (originX < (SCREEN_WIDTH + GHOST_DISTANCE - GHOST_MARGIN)) ratio1 = (originX-SCREEN_WIDTH+GHOST_MARGIN)/GHOST_DISTANCE;
		else ratio1 = 1;
	}
	// Dans la zone visible de l'écran (en X)
	else {
		ghostBubble->setOriginX(originX);
		ratio1 = 0;
	}

	// Au dessus de l'écran
	if (originY < GHOST_MARGIN){
		ghostBubble->setOriginY(GHOST_MARGIN);
		if (originY > - GHOST_DISTANCE + GHOST_MARGIN) ratio2 = (-originY+GHOST_MARGIN)/GHOST_DISTANCE;
		else ratio2 = 1;
	}
	// Dans la zone visible de l'écran (en Y)
	else {
		ghostBubble->setOriginY(originY);
		ratio2 = 0;
	}

	/* Calcul des angles de la bulle et de l'aperçu de la munition */
	ghostBubble->setPolygonAngle(atan2(ghostBubble->getAbsoluteOriginY()-getAbsoluteOriginY(),ghostBubble->getAbsoluteOriginX()-getAbsoluteOriginX()));
	ghostAmmo->setPolygonAngle(angle-ghostBubble->getAbsolutePolygonAngle());

	/* Calcul de la transparence de la bulle */
	u32 filter = colorFadeOut(WHITE, TRANSPARENT, max(ratio1,ratio2));
	ghostAmmo->setColorFilter(filter);
	ghostBubble->setColorFilter(filter);
}

void Ammo::computeSmoklets(){
	if (!timeIsOver()) return;
	manager->addAnimation(
		new Animation(
			SMOKLET_LAYER,
			App::imageBank->get(TXT_SMOKE),
			originX,
			originY,
			0,0,0,NULL,
			SMOKE_WIDTH,
			SMOKE_HEIGHT,
			SMOKE_DURATION,
			SMOKE_SLOW,
			1,
			new PolyDeg2(manager->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_SMOKE/(2*100* SMOKE_WEIGHT),0,originX),
			new PolyDeg2(-GRAVITY*SMOKE_AIR_RESISTANCE/2,0,originY)));
}

void Ammo::compute() {
	if (!fired) return;
	Timer::compute();
	computePosition();
	computeSmoklets();
	computeGhost();
	computeOut();
}

void Ammo::setAngle(const float _angle){
	angle = _angle;
}

void Ammo::destroy() {
	destroyed = true;
}

void Ammo::outCannon(){
	outOfCannon = true;
	getGhostAmmo()->show();
	getGhostBubble()->show();
}

void Ammo::outShield(){
	outOfShield = true;
}

void Ammo::deleteMe(){
	toDelete = true;
}

bool Ammo::isToDelete(){
	return toDelete;
}

bool Ammo::isOutOfCannon() const{
	return outOfCannon;
}

bool Ammo::isOutOfShield() const{
	return outOfShield;
}

bool Ammo::isOffScreen() const{
	for (unsigned int i=0,size=vertices.size();i<size;i++){
		if (vertices[i].getX() >= 0 && vertices[i].getX() < terrain->getCols()*terrain->getCellWidth()) return false;
	}
	return true;
}

bool Ammo::isTooLow() const{
	return (originY > SCREEN_HEIGHT);
}

bool Ammo::isDestroyed() const{
  return destroyed;
}

bool Ammo::hitTheGround(Terrain* terrain) const{
	vector<Coordinates> v = getRotatedVertices();
	for (int i=0,size=v.size();i<size;i++){
		if (v[i].getY()+getAbsoluteY() >= terrain->getHeight(v[i].getX()+getAbsoluteX())) return true;
	}
	return false;
}

bool Ammo::hitABonus(list<Bonus*>* bonusList) const{
	list<Bonus*>::iterator it;
	for (it = bonusList->begin();it!=bonusList->end();it++){
		if (intersect(*it)) {
			// Ici on fait attention à gérer le cas improbable ou 2 munitions toucheraient le bonus à la même frame
			if (!(*it)->isPossessed()) {
				owner->addBonus(*it);
				return true;
			}
		}
	}
	return false;
}

Ammo* Ammo::hitAnotherAmmo(list<Ammo*>* ammoList) const{
	list<Ammo*>::iterator it;
	for (it = ammoList->begin();it!=ammoList->end();it++)
		if (this != *it && intersect(*it)) return *it;
	return NULL;
}

Player* Ammo::hitAPlayer(Player* player1, Player* player2) const{
	if (!isOutOfCannon()) return NULL;
	if (intersect(player1)) return player1;
	if (intersect(player2)) return player2;
	return NULL;
}

bool Ammo::hitAShield(Player* player){
	if (!player->isInShieldMode()) return false;
	float xDiff = player->getAbsoluteX() - getAbsoluteX();
	float yDiff = player->getAbsoluteY() - getAbsoluteY();
	float playerAmmoAngle =  atan2(yDiff,xDiff) - PI/2;
	float shieldRadius = SHIELD_WIDTH/2;
	// Si je suis en dehors d'un bouclier, pas de collision
	if (xDiff*xDiff + yDiff*yDiff > shieldRadius*shieldRadius) {
		// J'autorise les collisions futures éventuelles avec un bouclier,
		// seulement si je suis en dehors du bouclier du propriétaire
		if (getOwner() == player && !isOutOfShield()) {
			addShieldEffect(player,playerAmmoAngle);
			outShield();
		}
		return false;
	}
	if (getOwner() == player && !isOutOfShield()) return false;
	addShieldEffect(player,playerAmmoAngle);
	return true;
}

void Ammo::addShieldEffect(Player* player, float angle) const{
	Animation* shiningShield = new Animation(
			SHIELD_LAYER,
			App::imageBank->get(TXT_SHIELD),
			0,
			0,
			0,0,angle,player,
			SHIELD_WIDTH,
			SHIELD_HEIGHT,
			SHIELD_DURATION,
			SHIELD_SLOW,
			1);
	shiningShield->setSpinFather(false);
	manager->addAnimation(shiningShield);
}

void Ammo::init(float strength){
	float angle = getAbsolutePolygonAngle(), cosinus = cos(angle), sinus = sin(angle);
	calcX->setC(getAbsoluteOriginX() + CANNON_LENGTH * cosinus); // X
	calcY->setC(getAbsoluteOriginY() + CANNON_LENGTH * sinus); // Y
	calcX->setB(strength * cosinus); // X
	calcY->setB(strength * sinus); // Y
	setFather(NULL);	//< On libère la munition de l'emprise de son père (comme c'est beau)
	fire();
	setRadial(0);		//< On réaligne le centre de gravité (décalé pour dépasser du canon)
	compute();			//< On initialise la position, car dans le canon elle est relative !
	manager->addAmmo(this);
}

void Ammo::fire(){
	fired = true;
	getGhostAmmo()->show();
	getGhostBubble()->show();
}

}


