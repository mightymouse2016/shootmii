#include "../ShootMii.h"

namespace shootmii {

Cloud::Cloud(
		const LayerPriority _layer,
		Wind* _wind,
		GRRLIB_texImg* _image,
		const int _width,
		const int _height) :
	Rectangle(_layer, _width, _height, 0, 0, 0, 0, 0, 0, _image),
	wind(_wind),
	t(0)
{
	randomX();
	randomY();
}

void Cloud::updateT() {
	if (t > slow) t = 0;
	else t++;
}

void Cloud::updateX() {
	if (!t){
		if (wind->getWindDirection()){
			if (originX - getWidth()/2 > SCREEN_WIDTH) {
				originX = - getWidth()/2;
				randomY();
			} else originX++;
		}
		else {
			if (originX < - getWidth()/2){
				originX = SCREEN_WIDTH + getWidth()/2;
				randomY();
			} else originX--;
		}
	}
}

void Cloud::randomX() {
	originX = rand()%static_cast<int>(getWidth() + SCREEN_WIDTH) - getWidth()/2;
}

void Cloud::randomY() {
	originY = rand()%static_cast<int>(SCREEN_HEIGHT*CLOUD_SPACE/100) + getHeight()/2;
}

void Cloud::init() {
	slow = (MAX_WIND_SPEED-wind->getWindSpeed())*WIND_INFLUENCE_ON_CLOUDS/100;
	randomX();
	randomY();
}

}
