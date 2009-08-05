#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "../ShootMii.h"

namespace shootmii {

class TitleScreen : public Screen {
private:
	GRRLIB_texImg* tex_title_screen;
	GRRLIB_texImg tex_font;
public:
	TitleScreen(App*);
	virtual ~TitleScreen();
	void draw();
	void dealEvent(const u32*, const u32*);
};

}

#endif // __TITLE_SCREEN_H__
