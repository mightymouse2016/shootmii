#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "../ShootMii.h"

namespace shootmii {

class Coordinates {
private:
	float x;
	float y;
public:
	Coordinates(const float _x = 0, const float _y = 0);
	int getX() const;
	int getY() const;
	void setX(const int _x);
	void setY(const int _y);
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
