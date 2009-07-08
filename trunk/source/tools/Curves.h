#ifndef CURVES_H_
#define CURVES_H_

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

class Function {
protected:
	float a;
	float b;
	float c;
public:
	Function(const float _a = 0, const float _b = 0, const float _c = 0);
	virtual float operator()(const float t) const=0; // la fonction
	virtual float operator[](const float t) const=0; // la dérivée
	void setA(float _a);
	void setB(float _b);
	void setC(float _c);
};

// Exemple d'objet fonctionnel (foncteur) : f(t)=at²+bt+c
class PolyDeg2: public Function {
public:
	PolyDeg2(const float _a = 0, const float _b = 0, const float _c = 0);
	float operator()(const float t) const;
	float operator[](const float t) const;
};

class Affine: public Function {
public:
	Affine(const float _a = 0, const float _b = 0);
	float operator()(const float t) const;
	float operator[](const float t) const;
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

#endif
