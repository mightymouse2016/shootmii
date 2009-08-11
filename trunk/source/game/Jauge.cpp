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
		const float angle,
		Polygon* father) :
	Rectangle(JAUGE_LAYER,width,height,originX,originY,0,angle,0,1,NULL,father),
	percentage(_percentage)
{
	//recursive = false;
	for(int i=0;i<width;i++){
		addChild(new Rectangle(JAUGE_LAYER,1,height,-width/2+i+1,0,0,0,0,1,image,this,i,1,height));
	}
}

void Jauge::compute(){
	int width = getWidth();
	int limit = static_cast<int>(width*(*percentage)/100);
	for(int i=0;i<limit;i++) children[i]->show();
	for(int i=limit;i<width;i++) children[i]->hide();
}

}
