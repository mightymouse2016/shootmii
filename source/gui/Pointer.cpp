#include "../ShootMii.h"

namespace shootmii {

Pointer::Pointer(GRRLIB_texImg* image) :
	Rectangle(
		POINTER_LAYER,
		POINTER_WIDTH,
		POINTER_HEIGHT,
		0,0,0,0,0,1,
		image,
		NULL,0,
		POINTER_WIDTH,
		POINTER_HEIGHT,
		true)
{
	// NOTHING TO DO
}

}
