#include "../ShootMii.h"

namespace shootmii {

  Cannon::Cannon(const float _angleOffSet, const float _angleRange,
    const float _angle, const float _rotationStep) :
    angleOffSet(_angleOffSet), angleRange(_angleRange), angle(_angle),
        rotationStep(_rotationStep), loadedAmmo(new CannonBall), strength(0),
        heat(0), blockedTime(0), heatCool(0), reloadTime(0) {
  }

  Cannon::~Cannon() {
    if (loadedAmmo) delete loadedAmmo;
  }

  void Cannon::init() {
    strength = 0;
    heat = 0;
    blockedTime = 0;
    heatCool = 0;
    reloadTime = 0;
    if(!loadedAmmo) loadedAmmo = new CannonBall;
  }
  
  int Cannon::getStrength() const {
    return strength;
  }

  int Cannon::getHeat() const {
    return heat;
  }
  
  int Cannon::getBlockedTime() const{
    return blockedTime;
  }

  void Cannon::decHeat() {
    heatCool++;
    if(heatCool > 10) {
      heatCool = 0;
    }
    u32 currentTime = ticks_to_millisecs(gettime());
    
    // Mode bloqu� quand on a harcel� le canon
    if (heat == 100){
      if(currentTime - blockedTime > BLOCKING_TIME) heat -= 1;
    }
    // Mode lent quand le canon est chaud
    else if (heat > 50){
      if (!(heatCool%HEAT_COOL_SLOW)) heat -= 1;
    }
    // Mode normal 50 premiers % de la jauge
    else if (heat > 0){
      if (!(heatCool%HEAT_COOL_FAST)) heat -= 1;
    }
    reload();
  }

  void Cannon::draw(const int screenX, const int screenY, const int cellSize) const {
    float topCos = cos(angle*PI/180);
    float topSin = sin(angle*PI/180);
    float topX = CANNON_LENGTH*topCos;
    float topY = CANNON_LENGTH*topSin;
    // On dessine la ligne
    GRRLIB_Line(screenX+cellSize/2, screenY+cellSize/2, screenX+cellSize/2+topX,
        screenY+cellSize/2-topY, BLACK);
    // On dessine la munition
    if (loadedAmmo){
      loadedAmmo->setScreenX(screenX+topX);
      loadedAmmo->setScreenY(screenY-topY);
      loadedAmmo->draw();
    }
  }

void Cannon::rotateLeft() {
  if (angle + rotationStep < angleOffSet + angleRange)
    angle += rotationStep;
}

void Cannon::rotateRight() {
  if (angle - rotationStep> angleOffSet)
    angle -= rotationStep;
}

void Cannon::shoot(Manager* manager) {
  // Si le canon est trop chaud, on ne peux pas tirer
  if (heat == 100) {
    return;
  }
  
  if (loadedAmmo) {
  
  // Saturation du canon
  if (heat+HEAT_STEP >= 100){
    heat = 100;
    blockedTime = ticks_to_millisecs(gettime());
  }
  // Ou incr�mentation normale
  else {
    heat+=HEAT_STEP;
  }
  
    float topCos = cos(angle*PI/180);
    float topSin = sin(angle*PI/180);
    // Mise � jour des coefficients qui d�finissent l'inclinaison de la courbe (si on a boug� le cannon)
    loadedAmmo->getCalcX()->setB(loadedAmmo->getScreenX()+CANNON_LENGTH*topCos); // X
    loadedAmmo->getCalcY()->setC(loadedAmmo->getScreenY()-CANNON_LENGTH*topSin); // Y
    loadedAmmo->getCalcX()->setA(DEFAULT_POWER*topCos); // X
    loadedAmmo->getCalcY()->setB(-DEFAULT_POWER*topSin); // Y
    // On confie la munition au manager
    manager->addAmmosToDraw(loadedAmmo);
    loadedAmmo = NULL;
  }
  
}

void Cannon::reload(){
  if (!loadedAmmo){
    if (reloadTime > RELOAD_TIME){
      loadedAmmo = new CannonBall;
      reloadTime = 0;
    }
    else {
      reloadTime++;
    }
  }
}

}