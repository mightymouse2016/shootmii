#ifndef POLYGON_H_
#define POLYGON_H_

#include "../ShootMii.h"

namespace shootmii {

/*
 * Cette structure permet de crééer des squelettes
 * father permet d'obtenir les coordonnées du père,
 * ainsi on travaille ici en relatif.
 */

/* Uniquement pour les quadrilatère */
enum Corner{
	UP_LEFT,
	UP_RIGHT,
	DOWN_RIGHT,
	DOWN_LEFT
};

const int ORIGIN_CROSS_WIDTH(2);
const int ORIGIN_CROSS_HEIGHT(2);

bool intervalIntersect(const float MA1,const float MA2,const float MB1,const float MB2);
bool segmentIntersect(Coordinates a, Coordinates A, Coordinates b, Coordinates B);

class Polygon{
protected:
	float originX; // L'origine relative
	float originY;
	float radial;
	float spin; //0 -> translation circulaire. 1 -> rotation synchrone. autre -> rotation asynchrone
	float angle;
	float polygonAngle;
	Polygon* father;
	vector<Polygon*> children; //Pour le destructeur
	vector<Coordinates> vertices;
	Coordinates drawOrigin;
	GRRLIB_texImg* image;
	int spriteIndex;
	int spriteWidth;
	int spriteHeight;
public:
	Polygon(
		const float originX = 0,
		const float originY = 0,
		const float radial = 0,
		const float angle = 0,
		const float polygonAngle = 0,
		const float spin = 1,
		Polygon* father = NULL,
		Coordinates drawOrigin = Coordinates(0,0),
		GRRLIB_texImg* image = NULL,
		const int spriteIndex = 0,
		const int spriteWidth = 0,
		const int spriteHeight = 0);
	~Polygon();

	const vector<Coordinates>& getVertices() const;
	vector<Coordinates> getRotatedVertices() const;
	const Coordinates& getDrawOrigin() const;
	const Coordinates getRotatedDrawOrigin() const;
	float getOriginX() const;
	float getOriginY() const;
	float getAbsoluteOriginX() const;
	float getAbsoluteOriginY() const;
	float getX() const;
	float getY() const;
	float getAbsoluteX() const;
	float getAbsoluteY() const;
	float getRadial() const;
	float getSpin() const;
	float getAngle() const;
	float getAbsoluteAngle() const;
	float getPolygonAngle() const;
	float getAbsolutePolygonAngle() const;
	Polygon* getFather() const;

	void setOriginX(const int originX);
	void setOriginY(const int originY);
	void setRadial(const float radial);
	void setSpin(const float spin);
	void setAngle(const float angle);
	void setFather(Polygon* father);

	void addChild(Polygon * child);

	void rotate(const float deltaAngle);
	void lengthenRadial(const float deltaRadial);
	void translateX(const float deltaX);
	void translateY(const float deltaY);
	void translate(const float deltaX,const float deltaY);
	void grow(const float k);

	void draw() const;

	bool intersect(Polygon* polygon) const;

};

}

#endif /* POLYGON_H_ */
