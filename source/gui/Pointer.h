#ifndef POINTER_H_
#define POINTER_H_

#include "../ShootMii.h"

namespace shootmii {

const int POINTER_WIDTH(96);
const int POINTER_HEIGHT(96);

class Pointer : public Rectangle {
private:

public:
	Pointer(GRRLIB_texImg* image);
};

}

#endif /* POINTER_H_ */
