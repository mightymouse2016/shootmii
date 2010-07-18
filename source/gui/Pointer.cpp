#include "../tools/ImageBank.h"
#include "../tools/Tools.h"
#include "../math/Rectangle.h"
#include "../App.h"
#include "Pointer.h"

namespace shootmii {

Pointer::Pointer(int _playerNumber, App* _app) :
	Rectangle(
		POINTER_LAYER,
		POINTER_WIDTH,
		POINTER_HEIGHT,
		0,0,0,0,0,true,true,
		NULL,
		NULL,0,
		POINTER_WIDTH,
		POINTER_HEIGHT,
		true),
	playerNumber(_playerNumber),
	clicking(false),
	app(_app)
{
	switch (playerNumber){
	case 1:
		app->getEventsPlayer()[0] = events;
		channel = WPAD_CHAN_0;
		setImage(App::imageBank->get(TXT_POINTER_1));
		break;
	case 2:
		app->getEventsPlayer()[1] = events;
		channel = WPAD_CHAN_1;
		setImage(App::imageBank->get(TXT_POINTER_2));
		break;
	}
}

Pointer::~Pointer()
{
	// NOTHING TO DO
}

bool Pointer::isCliking() const{
	return clicking;
}

void Pointer::drawDebug() const{
	Polygon::drawDebug();
	int x = getAbsoluteOriginX();
	int y = getAbsoluteOriginY();
	int w = 10;
	int h = 10;
	GRRLIB_Line(x-w,y-h,x+w,y+h,Color::BLACK);
	GRRLIB_Line(x-w,y+h,x+w,y-h,Color::BLACK);
}

void Pointer::dealEvent(){
	// Mise à jour des coordonnées du pointeur
	if (WPAD_Probe(channel, NULL) == WPAD_ERR_NONE) {
		WPADData* wd = WPAD_Data(channel);
		if(wd->ir.valid) {
			show();
			setOriginX(wd->ir.x*2-SCREEN_WIDTH/2);
			setOriginY(wd->ir.y*2-SCREEN_HEIGHT/2);
			setPolygonAngle(wd->ir.angle*PI/180);
		}
		else{
			hide();
		}
	}
	// Mise à jour des événements
	events[HELD] = 	WPAD_ButtonsHeld(channel);
	events[DOWN] = 	WPAD_ButtonsDown(channel);
	events[UP] = 	WPAD_ButtonsUp(channel);

	if (events[DOWN] & WPAD_BUTTON_A) clicking = true;
	else clicking = false;
}

}
