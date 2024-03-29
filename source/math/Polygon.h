#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include "GRRLIB.h"
#include "Segment.h"
#include "Coordinates.h"
#include "../tools/Color.h"

namespace shootmii {

/*
 * Cette structure permet de cr��er des squelettes
 * father permet d'obtenir les coordonn�es du p�re,
 * ainsi on travaille ici en relatif.
 */

/* Uniquement pour les quadrilat�re */
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
	BACK_CLOUD_LAYER,
	STRENGTH_JAUGE_LAYER,
	CROSSHAIR_LAYER,
	CANNON_LAYER,
	TANK_LAYER,
	FRONT_SMOKLET_LAYER,
	GHOST_LAYER,
	STATUS_BAR_LAYER,
	JAUGE_LAYER,
	BONUS_LAYER,
	SHIELD_LAYER,
	EXPLOSION_LAYER,
	FRONT_CLOUD_LAYER,
	DOCK_LAYER,
	BUTTON_LAYER,
	HIGHLIGHT_LAYER,
	TEXT_LAYER,
	POINTER_LAYER
};

const float PI(3.14159265358979323846264338327950288419716939937510);

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
	float spinFather; //0 -> translation circulaire. 1 -> rotation synchrone. autre -> rotation asynchrone
	float spinPolygon; //0 -> translation circulaire. 1 -> rotation synchrone. autre -> rotation asynchrone
	float angle;
	float polygonAngle;
	float scale;
	Polygon* father;
	std::vector<Polygon*> children; //Pour le destructeur
	std::vector<Coordinates> vertices;
	Coordinates drawOrigin;
	GRRLIB_texImg* image;
	int spriteIndex;
	int spriteWidth;
	int spriteHeight;
	bool hidden;
	bool debugHidden;
	bool recursive;
	Color colorFilter;
public:
	Polygon(
		const LayerPriority layer,
		const float originX = 0,
		const float originY = 0,
		const float radial = 0,
		const float angle = 0,
		const float polygonAngle = 0,
		const bool spinFather = true,
		const bool spinPolygon = true,
		Polygon* father = NULL,
		Coordinates drawOrigin = Coordinates(0,0),
		GRRLIB_texImg* image = NULL,
		const int spriteIndex = 0,
		const int spriteWidth = 0,
		const int spriteHeight = 0,
		const bool hidden = false,
		const bool debugHidden = false);
	~Polygon();

	const std::vector<Coordinates>& getVertices() const;
	std::vector<Coordinates> getRotatedVertices() const;
	std::vector<Coordinates> getRotatedAbsoluteVertices() const;
	std::vector<Segment> getEdges() const;
	std::vector<Segment> getRotatedEdges() const;
	std::vector<Segment> getRotatedAbsoluteEdges() const;
	const Coordinates& getDrawOrigin() const;
	const Coordinates getRotatedDrawOrigin() const;
	static int getNumberOfPolygonsInstances();
	LayerPriority getLayer() const;
	Coordinates getAbsoluteOrigin() const;
	float getAbsoluteOriginX() const;
	float getAbsoluteOriginY() const;
	Coordinates getAbsoluteCoordinates() const;
	float getAbsoluteX() const;
	float getAbsoluteY() const;
	float getAbsoluteAngle() const;
	float getAbsolutePolygonAngle() const;
	Polygon* getFather() const;
	const Color& getColorFilter() const;
	std::vector<Polygon*>& getChildren();
	const std::vector<Polygon*>& getChildren() const;

	void setOriginX(const float originX);
	void setOriginY(const float originY);
	void setRadial(const float radial);
	void setSpinFather(const bool spinFather);
	void setSpinPolygon(const bool spinPolygon);
	void setAngle(const float angle);
	void setPolygonAngle(const float polygonAngle);
	void setScale(const float scale);
	void setFather(Polygon* father);
	void setImage(GRRLIB_texImg* image);
	void setColorFilter(const Color& colorFilter);
	void setSprite(const int spriteIndex);

	void addChild(Polygon * child);

	void rotate(const float deltaAngle);
	void lengthenRadial(const float deltaRadial);
	void translateX(const float deltaX);
	void translateY(const float deltaY);
	void translate(const float deltaX,const float deltaY);
	void grow(const float k);

	virtual void addToDrawManager();
	virtual void draw() const;
	virtual void draw(const Color& colorFilter, const int spriteIndex) const;
	virtual void drawDebug() const;
	void hide();
	void show();

	bool intersect(const Polygon* const polygon) const;
	bool intersect(const Segment& s) const;
};

}

#endif /* POLYGON_H_ */
