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

/* Ordre d'affichage */
enum LayerPriority{
	SKY_LAYER,
	SUN_LAYER,
	SMOKLET_LAYER,
	TERRAIN_LAYER,
	AMMO_LAYER,
	STATUS_BAR_LAYER,
	JAUGE_LAYER,
	BACK_CLOUD_LAYER,
	STRENGTH_JAUGE_LAYER,
	CROSSHAIR_LAYER,
	CANNON_LAYER,
	TANK_LAYER,
	BONUS_LAYER,
	EXPLOSION_LAYER,
	FRONT_CLOUD_LAYER,
	GHOST_LAYER
};

const int ORIGIN_CROSS_WIDTH(3);
const int ORIGIN_CROSS_HEIGHT(3);

class Polygon{
private:
	static int numberOfPolygonsInstances;
protected:
	LayerPriority layer; // La couche d'affichage
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
	bool hidden;
	bool debugHidden;
	bool recursive;
	u32 colorFilter;
public:
	Polygon(
		const LayerPriority layer,
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
		const int spriteHeight = 0,
		const bool hidden = false,
		const bool debugHidden = false);
	~Polygon();

	const vector<Coordinates>& getVertices() const;
	vector<Coordinates> getRotatedVertices() const;
	const Coordinates& getDrawOrigin() const;
	const Coordinates getRotatedDrawOrigin() const;
	static int getNumberOfPolygonsInstances();
	LayerPriority getLayer() const;
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
	u32 getColorFilter() const;

	void setOriginX(const float originX);
	void setOriginY(const float originY);
	void setRadial(const float radial);
	void setSpin(const float spin);
	void setAngle(const float angle);
	void setPolygonAngle(const float polygonAngle);
	void setFather(Polygon* father);
	void setImage(GRRLIB_texImg* image);
	void setColorFilter(const u32 colorFilter);

	void addChild(Polygon * child);

	void rotate(const float deltaAngle);
	void lengthenRadial(const float deltaRadial);
	void translateX(const float deltaX);
	void translateY(const float deltaY);
	void translate(const float deltaX,const float deltaY);
	void grow(const float k);

	virtual void addToDrawManager();
	virtual void draw() const;// utiliser addToDrawManager() qui prendras en compte le layer et appelera draw() au bon moment
	virtual void drawDebug() const;
	void hide();
	void show();

	bool intersect(Polygon* polygon) const;
};

}

#endif /* POLYGON_H_ */
