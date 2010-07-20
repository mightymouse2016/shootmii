#include "../math/Polygon.h"
#include "../gfx/font_console.h"
#include "Tools.h"
#include "Console.h"

namespace shootmii {

Console::Console() :
	fps(0),
	debug(false),
	console_font(loadFont(font_console, 8, 0))
{
	// NOTHING TO DO
}

void Console::addDebug(const char* txt, ...) {
	if (debug) {
		if (history.size() == MAX_HISTORY) history.erase(history.begin());
		char buf[1024];
		va_list argp;
		va_start(argp, txt);
		vsprintf(buf, txt, argp);
		va_end(argp);
		history.push_back(buf);
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

void Console::draw() const{
	if (debug) {
		drawFPS();
		drawTime();
		drawPolygonsInstances();
		// Affichage du BACKGROUND
		GRRLIB_Rectangle(CONSOLE_X_OFFSET, CONSOLE_Y_OFFSET, SCREEN_WIDTH - 2*CONSOLE_X_OFFSET , CONSOLE_HEIGHT, Color::CONSOLE_COLOR, true);
		// Affichage des debug
		for (u8 i = 0; i < history.size(); i++)
			GRRLIB_Printf(CONSOLE_TEXT_X_OFFSET, CONSOLE_Y_OFFSET + (i + 1)*CONSOLE_TEXT_Y_OFFSET, console_font, Color::WHITE, 1,history[i].c_str());
	}
}

void Console::drawFPS() const{
	// Affichage du BACKGROUND
	GRRLIB_Rectangle(CONSOLE_X_OFFSET, CONSOLE_X_OFFSET, CONSOLE_FPS_BG_WIDTH,25, Color::CONSOLE_COLOR, true);
	// Affichage des FPS
	GRRLIB_Printf(CONSOLE_X_OFFSET + 10, CONSOLE_X_OFFSET + 10, console_font, Color::WHITE, 1, "FPS: %d", fps);
}

void Console::drawPolygonsInstances() const{
	// Affichage du BACKGROUND
	GRRLIB_Rectangle(CONSOLE_X_OFFSET + 140, CONSOLE_X_OFFSET, 150 ,25, Color::CONSOLE_COLOR, true);
	// Affichage des FPS
	GRRLIB_Printf(CONSOLE_X_OFFSET + 150, CONSOLE_X_OFFSET + 10, console_font,Color::WHITE, 1, "Polygons : %d", Polygon::getNumberOfPolygonsInstances());
}

void Console::setFPS(u8 fps) {
  this->fps = fps;
}

void Console::drawTime() const{
	u8 seconds = ticks_to_secs(gettime());
	u8 minutes = seconds / 60;
	u8 hours = minutes / 60;
	// Affichage du BACKGROUND
	GRRLIB_Rectangle(SCREEN_WIDTH - CONSOLE_TIME_BG_WIDTH - CONSOLE_X_OFFSET, CONSOLE_X_OFFSET, CONSOLE_TIME_BG_WIDTH, 25, Color::CONSOLE_COLOR, true);
	// Affichage du temps
	GRRLIB_Printf(SCREEN_WIDTH - CONSOLE_TIME_BG_WIDTH - CONSOLE_X_OFFSET + 10, CONSOLE_X_OFFSET + 10, console_font, Color::WHITE, 1, "TIME: %d:%d:%d", hours, minutes, seconds);
}

}
