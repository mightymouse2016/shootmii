#include "../ShootMii.h"

namespace shootmii {

Jauge::Jauge(
		const LayerPriority layer,
		float* _percentage,
		const float width,
		const float height,
		const float originX,
		const float originY,
		GRRLIB_texImg* image,
		bool* _flickering,
		const float angle,
		Polygon* father) :
	Rectangle(JAUGE_LAYER,width,height,originX,originY,0,angle,0,true,true,NULL,father),
	percentage(_percentage),
	flickering(_flickering),
	flickeringState(0),
	flickeringDirection(false)
{
	for(int i=0;i<width;i++){
		addChild(new Rectangle(JAUGE_LAYER,1,height,-width/2+i+1,0,0,0,0,true,true,image,this,i,1,height,false,true));
	}
}

void Jauge::compute(){
	if (flickeringDirection){
		flickeringState += FLICKERING_SPEED;
		if (flickeringState > FLICKERING_MAX) {
			flickeringState = FLICKERING_MAX;
			flickeringDirection = !flickeringDirection;
		}
	}
	else {
		flickeringState -= FLICKERING_SPEED;
		if (flickeringState < FLICKERING_MIN) {
			flickeringState = FLICKERING_MIN;
			flickeringDirection = !flickeringDirection;
		}
	}

	if (flickering) setColorFilter(*flickering ? colorFadeOut(RED & TRANSPARENT, RED, flickeringState) : TRANSPARENT);

	int width = getWidth();
	int limit = static_cast<int>(width*(*percentage)/100);
	for(int i=0;i<limit;i++) {
		children[i]->show();
		children[i]->setColorFilter(getColorFilter());
	}
	for(int i=limit;i<width;i++) children[i]->hide();

}

}
