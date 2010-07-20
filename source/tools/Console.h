#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "GRRLIB.h"
#include <vector>
#include <string>
#include <cstdarg>
#include <ctime>
#include <ogc/lwp_watchdog.h>

namespace shootmii {

static const unsigned char MAX_HISTORY = 15;
static const unsigned char CONSOLE_HEIGHT = 180;
static const unsigned char CONSOLE_X_OFFSET = 15;
static const unsigned char CONSOLE_Y_OFFSET = 50;
static const unsigned char CONSOLE_TEXT_X_OFFSET = 25;
static const unsigned char CONSOLE_TEXT_Y_OFFSET = 10;
static const unsigned char CONSOLE_FPS_BG_WIDTH = 75;
static const unsigned char CONSOLE_TIME_BG_WIDTH = 150;

class Console {
private:
	unsigned char screenY;
	unsigned char fps;
	bool debug;
	GRRLIB_texImg* console_font;
	std::vector<std::string> history;
	void drawFPS() const;
	void drawTime() const;
	void drawPolygonsInstances() const;
public:
	Console();
	void draw() const;
	void addDebug(const char* txt, ...);
	bool isDebug() const;
	void toggleDebug();
	void setFPS(unsigned char fps);

};

}

#endif /*CONSOLE_H_*/
