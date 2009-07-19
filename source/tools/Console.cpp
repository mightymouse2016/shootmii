#include "../ShootMii.h"

namespace shootmii {

Console::Console() :
	fps(0),
	debug(false),
	console_font(loadFont(font_console, 8, 0))
{

}

Console::~Console() {
	// NOTHING TO DO
}

void Console::addDebug(string txt) {
	if (debug) {
		if (history.size() == MAX_HISTORY) history.erase(history.begin());
		history.push_back(txt);
	}
}

bool Console::isDebug() const {
  return debug;
}

void Console::toggleDebug() {
  debug = !debug;
  if(debug) {
    this->addDebug("passage en mode debug !!!");
  }
}

void Console::draw() {
	if (debug) {
		drawFPS();
		drawTime();
		// Affichage du BACKGROUND
		GRRLIB_Rectangle(CONSOLE_X_OFFSET, CONSOLE_Y_OFFSET, SCREEN_WIDTH - 2*CONSOLE_X_OFFSET , CONSOLE_HEIGHT, CONSOLE_COLOR, true);
		// Affichage des debug
		for (u8 i = 0; i < history.size(); i++)
			GRRLIB_Printf(CONSOLE_TEXT_X_OFFSET, CONSOLE_Y_OFFSET + (i + 1)*CONSOLE_TEXT_Y_OFFSET, console_font, WHITE, 1,history[i].c_str());
	}
}

void Console::drawFPS() {
	// Affichage du BACKGROUND
	GRRLIB_Rectangle(CONSOLE_X_OFFSET, CONSOLE_X_OFFSET, CONSOLE_FPS_BG_WIDTH,25, CONSOLE_COLOR, true);
	// Affichage des FPS
	GRRLIB_Printf(CONSOLE_X_OFFSET + 10, CONSOLE_X_OFFSET + 10, console_font,WHITE, 1, "FPS: %d", fps);
}

void Console::setFPS(u8 fps) {
  this->fps = fps;
}

void Console::drawTime() {
	u8 seconds = ticks_to_secs(gettime());
	u8 minutes = seconds / 60;
	u8 hours = minutes / 60;
	// Affichage du BACKGROUND
	GRRLIB_Rectangle(SCREEN_WIDTH - CONSOLE_TIME_BG_WIDTH - CONSOLE_X_OFFSET, CONSOLE_X_OFFSET, CONSOLE_TIME_BG_WIDTH, 25, CONSOLE_COLOR, true);
	// Affichage du temps
	GRRLIB_Printf(SCREEN_WIDTH - CONSOLE_TIME_BG_WIDTH - CONSOLE_X_OFFSET + 10, CONSOLE_X_OFFSET + 10, console_font, WHITE, 1, "TIME: %d:%d:%d", hours, minutes, seconds);
}

}
