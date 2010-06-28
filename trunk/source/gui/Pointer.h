#ifndef POINTER_H_
#define POINTER_H_

#include "GRRLIB.h"
#include <wiiuse/wpad.h>
#include "../math/Rectangle.h"

namespace shootmii {

class App;

const int POINTER_WIDTH(96);
const int POINTER_HEIGHT(96);

class Pointer : public Rectangle {
private:
	int playerNumber;
	bool clicking;
	App* app;
	u32 channel;
	u32 events[3];
public:
	Pointer(int playerNumber, App* app);
	~Pointer();
	bool isCliking() const;
	void drawDebug() const;
	void dealEvent();
};

}

#endif /* POINTER_H_ */
