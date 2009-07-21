#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "../ShootMii.h"

namespace shootmii {

class Explosion {
public:
	Explosion(
		GRRLIB_texImg* _tiles,
		const float _screenX,
		const float _screenY,
        const int _width,
        const int _height,
        const int _depth,
        const int _duration);
    ~Explosion();
    void draw();
    void compute();
    bool isFinished();

private:
    GRRLIB_texImg* tiles;
    float screenX;
    float screenY;
    int width;
    int height;
    int depth;
    int duration;
    int t;
};

}

#endif /*EXPLOSION_H_*/
