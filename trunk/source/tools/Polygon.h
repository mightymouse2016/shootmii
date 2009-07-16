#ifndef POLYGON_H_
#define POLYGON_H_

#include "../ShootMii.h"

namespace shootmii {

/*
 * Cette structure permet de crééer des squelettes
 * father permet d'obtenir les coordonnées du père,
 * ainsi on travaille ici en relatif.
 */

class Polygon{
private:
	float originX; // L'origine relative
	float originY;
	float radial;
	float spin; //0 -> translation circulaire. 1 -> rotation synchrone. autre -> rotation asynchrone
	float angle;
	Polygon* father;
	vector<Coordinates> vertices;
public:
	Polygon(
		vector<Coordinates> vertices,
		const float originX = 0,
		const float originY = 0,
		const float radial = 0,
		const float angle = 0,
		Polygon* father = NULL
	);

	const vector<Coordinates>& getVertices() const;
	vector<Coordinates>* getAbsoluteVertices() const;
	int getOriginX() const;
	int getOriginY() const;
	int getAbsoluteOriginX() const;
	int getAbsoluteOriginY() const;
	int getX() const;
	int getY() const;
	int getAbsoluteX() const;
	int getAbsoluteY() const;
	int getRadial() const;
	float getSpin() const;
	float getAngle() const;
	Polygon* getFather() const;

	void setOriginX(const int originX);
	void setOriginY(const int originY);
	void setRadial(const float radial);
	void setSpin(const float spin);
	void setAngle(const float angle);
	void setFather(Polygon* father);

	void rotate(const float deltaAngle);
	void lengthenRadial(const float deltaRadial);
	void translateX(const float deltaX);
	void translateY(const float deltaY);
	void translate(const float deltaX,const float deltaY);
	void grow(const float k);

	void draw() const;

};

}

#endif /* POLYGON_H_ */
