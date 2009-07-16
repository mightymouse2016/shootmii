#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "../ShootMii.h"

namespace shootmii {

class Coordinates {
private:
	float x;
	float y;
	float angle;
	float radial;
public:
	Coordinates(const float x = 0, const float y = 0);
	float getX() const;
	float getY() const;
	float getAngle() const;
	float getRadial() const;
	void setX(const float x);
	void setY(const float y);
	void setCoordinates(const float _x,const float _y);
	void grow(const float k);
	void growX(const float k);
	void growY(const float k);
};

// Fonction template qui prends en arguments un objet fonctionnel, un intervalle, un pas et qui retourne une liste de points
template<class T> list<Coordinates> * ComputeDots(const T& f, const float x1,
		const float x2, const float p) {
	list<Coordinates> * dotList = new list<Coordinates> ;
	Coordinates * c;
	for (float x = x1; x <= x2; x += p) {
		c = new Coordinates(x, f(x));
		dotList->push_back(*c);
	}
	return dotList;
}

}

#endif /* COORDINATES_H_ */
