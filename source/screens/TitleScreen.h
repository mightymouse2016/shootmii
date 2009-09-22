#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "../ShootMii.h"

namespace shootmii {

class TitleScreen : public Screen {
private:
	GRRLIB_texImg* tex_title_screen;
	GRRLIB_texImg* tex_font;
	Button* button_start;
	Pointer* pointer_player_1;
public:
	TitleScreen(
			App* app,
			Pointer** pointerPlayer,
			u32** eventsPlayer);
	void init();
	void dealEvent();
	void compute();
	void addToDrawManager();
};

}

#endif // __TITLE_SCREEN_H__
