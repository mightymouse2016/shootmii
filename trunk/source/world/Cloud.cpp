#include "../tools/Colors.h"
#include "../tools/Tools.h"
#include "Cloud.h"
#include "Wind.h"

namespace shootmii {

Cloud::Cloud(
		const LayerPriority _layer,
		Wind* _wind,
		GRRLIB_texImg* _image,
		const int _width,
		const int _height) :
	Rectangle(_layer, _width, _height, 0, 0, 0, 0, 0, false, false, _image),
	wind(_wind)
{
	randomX();
	randomY();
}

void Cloud::compute() {
	if (originX - getWidth()/2 > SCREEN_WIDTH) originX = - getWidth()/2;
	else if (originX + getWidth()/2 < 0) originX = SCREEN_WIDTH + getWidth()/2;
	if (getLayer() == BACK_CLOUD_LAYER){
		originX += wind->getWindSpeed()*WIND_INFLUENCE_ON_BACK_CLOUDS/100;
	}
	else{
		originX += wind->getWindSpeed()*WIND_INFLUENCE_ON_FRONT_CLOUDS/100;
	}
}

void Cloud::randomX() {
	originX = rand()%static_cast<int>(getWidth() + SCREEN_WIDTH) - getWidth()/2;
}

void Cloud::randomY() {
	originY = rand()%static_cast<int>(SCREEN_HEIGHT*CLOUD_SPACE/100) + getHeight()/2;
}

void Cloud::init() {
	randomX();
	randomY();
}

}
