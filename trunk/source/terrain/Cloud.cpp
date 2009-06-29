#include "../ShootMii.h"

namespace shootmii {

Cloud::Cloud(Wind* _wind, GRRLIB_texImg* _cloudImg, const int _cloudWidth, const int _cloudHeight) :
	wind(_wind), cloudImg(_cloudImg), cloudWidth(_cloudWidth), cloudHeight(_cloudHeight), t(0){
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
			if (screenX > SCREEN_WIDTH) {screenX = -cloudWidth; randomY();}
			else screenX++;
		}
		else {
			if (screenX < -cloudWidth) {screenX = SCREEN_WIDTH; randomY();}
			else screenX--;
		}
	}
}

void Cloud::randomX() {
	screenX = rand() % (cloudWidth + static_cast<int> (SCREEN_WIDTH)) - cloudWidth;
}

void Cloud::randomY() {
	screenY = rand() % (static_cast<int> (SCREEN_HEIGHT)*CLOUD_SPACE/100 - cloudHeight);
}

void Cloud::init() {
	slow = (MAX_WIND_SPEED-wind->getWindSpeed())*WIND_INFLUENCE_ON_CLOUDS/100;
	//app->getConsole()->addDebug(string("essai"));
	randomX();
	randomY();
}

void Cloud::draw() const {
	GRRLIB_DrawImg(screenX, screenY, *cloudImg, 0, 1, 1, WHITE);
}

}
