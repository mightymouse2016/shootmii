#include "../game/DrawManager.h"
#include "../tools/Colors.h"
#include "../tools/Tools.h"
#include "../App.h"
#include "Polygon.h"

namespace shootmii {

int Polygon::numberOfPolygonsInstances = 0;

Polygon::Polygon(
	const LayerPriority _layer,
	const float _originX,
	const float _originY,
	const float _radial,
	const float _angle,
	const float _polygonAngle,
	const bool _spinFather,
	const bool _spinPolygon,
	Polygon* _father,
	Coordinates _drawOrigin,
	GRRLIB_texImg* _image,
	const int _spriteIndex,
	const int _spriteWidth,
	const int _spriteHeight,
	const bool _hidden,
	const bool _debugHidden) :
		layer(_layer),
		originX(_originX),
		originY(_originY),
		radial(_radial),
		spinFather(_spinFather),
		spinPolygon(_spinPolygon),
		angle(_angle),
		polygonAngle(_polygonAngle),
		scale(1),
		father(_father),
		drawOrigin(_drawOrigin),
		image(_image),
		spriteIndex(_spriteIndex),
		spriteWidth(_spriteWidth),
		spriteHeight(_spriteHeight),
		hidden(_hidden),
		debugHidden(_debugHidden),
		recursive(true),
		colorFilter(WHITE)
{
	numberOfPolygonsInstances++;
	if (image){
		setImage(image);
	}
}

Polygon::~Polygon(){
	numberOfPolygonsInstances--;
	children.clear();
}

const std::vector<Coordinates>& Polygon::getVertices() const{
	return vertices;
}

std::vector<Coordinates> Polygon::getRotatedVertices() const{
	float verticeAngle;
	float verticeRadial;
	std::vector<Coordinates> rotatedVertices;
	rotatedVertices.reserve(vertices.size());
	for(int i=0,size=vertices.size();i<size;i++){
		verticeAngle =  vertices[i].getAngle();
		verticeRadial = vertices[i].getRadial();
		rotatedVertices.push_back(
			Coordinates(verticeRadial*cos(getAbsolutePolygonAngle()+verticeAngle),
						verticeRadial*sin(getAbsolutePolygonAngle()+verticeAngle)));
	}
	return rotatedVertices;
}

const Coordinates& Polygon::getDrawOrigin() const{
	return drawOrigin;
}

const Coordinates Polygon::getRotatedDrawOrigin() const{
	float drawOriginAngle = drawOrigin.getAngle();
	float drawOriginRadial = drawOrigin.getRadial();
	float absolutePolygonAngle = getAbsolutePolygonAngle();
	return Coordinates(drawOriginRadial*cos(absolutePolygonAngle+drawOriginAngle),drawOriginRadial*sin(absolutePolygonAngle+drawOriginAngle));
}

int Polygon::getNumberOfPolygonsInstances(){
	return numberOfPolygonsInstances;
}

LayerPriority Polygon::getLayer() const{
	return layer;
}

Coordinates Polygon::getAbsoluteOrigin() const{
	return Coordinates(getAbsoluteOriginX(),getAbsoluteOriginY());
}

float Polygon::getAbsoluteOriginX() const{
	// Si le polygon n'a pas de père, on s'aligne sur le coin supèrieur gauche de l'écran
	if (!father) return originX;

	// Sinon, on vérifie si le spin est activé, dans ce cas on se prend en compte l'angle du polygone père
	if (spinFather) return father->getAbsoluteX()
						+  originX*cos(father->getAbsolutePolygonAngle())
						+  originY*sin(father->getAbsolutePolygonAngle());

	// Sinon, on se base seulement sur  ses coordonnées
	return father->getAbsoluteX() + originX;
}

float Polygon::getAbsoluteOriginY() const{
	// Si le polygon n'a pas de père, on s'aligne sur le coin supèrieur gauche de l'écran
	if (!father) return originY;

	// Sinon, on vérifie si le spin est activé, dans ce cas on se prend en compte l'angle du polygone père
	if (spinFather) return father->getAbsoluteY()
						+  originX*sin(father->getAbsolutePolygonAngle())
						+  originY*cos(father->getAbsolutePolygonAngle());

	// Sinon, on se base seulement sur  ses coordonnées
	return father->getAbsoluteY() + originY;
}

float Polygon::getAbsoluteX() const{
	return getAbsoluteOriginX() + radial*cos(getAbsoluteAngle());
}

float Polygon::getAbsoluteY() const{
	return getAbsoluteOriginY() + radial*sin(getAbsoluteAngle());
}

float  Polygon::getAbsoluteAngle() const{
	if (father && spinFather) return father->getAbsolutePolygonAngle() + angle;
	return angle;
}

float  Polygon::getAbsolutePolygonAngle() const{
	if (spinPolygon) return getAbsoluteAngle() + polygonAngle;
	else return polygonAngle;
}

Polygon* Polygon::getFather() const{
	return father;
}

u32 Polygon::getColorFilter() const{
	return colorFilter;
}

std::vector<Polygon*>& Polygon::getChildren(){
	return children;
}

const std::vector<Polygon*>& Polygon::getChildren() const{
	return children;
}

void Polygon::setOriginX(const float _originX){
	originX = _originX;
}

void Polygon::setOriginY(const float _originY){
	originY = _originY;
}

void Polygon::setRadial(const float _radial){
	radial = _radial;
}

void Polygon::setSpinFather(const bool _spinFather){
	spinFather = _spinFather;
}

void Polygon::setSpinPolygon(const bool _spinPolygon){
	spinPolygon = _spinPolygon;
}

void Polygon::setAngle(const float _angle){
	angle = _angle;
}

void Polygon::setPolygonAngle(const float _polygonAngle){
	polygonAngle = _polygonAngle;
}

void Polygon::setScale(const float _scale){
	scale = _scale;
}

void Polygon::setFather(Polygon* _father){
	father = _father;
}

void Polygon::setImage(GRRLIB_texImg* _image){
	image = _image;
	if (spriteWidth && spriteHeight) { // Si c'est un sprite et non une image
		GRRLIB_InitTileSet(image, spriteWidth, spriteHeight, 0);
		image->handlex = 0; // Pour la compatibilité avec la nouvelle version de GRRLib
		image->handley = 0;
	} else {
		image->handlex = spriteWidth/2;
		image->handley = spriteHeight/2;
	}
}

void Polygon::setColorFilter(const u32 _colorFilter){
	colorFilter = _colorFilter;
}

void Polygon::setSprite(const int _spriteIndex){
	spriteIndex = _spriteIndex;
}

void Polygon::addChild(Polygon * child){
	children.push_back(child);
	if (child) child->setFather(this);
}

void Polygon::rotate(const float deltaAngle){
	angle += deltaAngle;
}

void Polygon::lengthenRadial(const float deltaRadial){
	radial += deltaRadial;
}

void Polygon::translateX(const float deltaX){
	originX += deltaX;
}

void Polygon::translateY(const float deltaY){
	originY += deltaY;
}

void Polygon::translate(const float deltaX,const float deltaY){
	originX += deltaX;
	originY += deltaY;
}

void Polygon::grow(const float k){
	scale*=k;
}

void Polygon::addToDrawManager(){
	if (!hidden) App::drawManager->addToDraw(this);
	if (recursive){
		for (int i=0,size=children.size();i<size;i++){
			if (children[i]) children[i]->addToDrawManager();
		}
	}
}

void Polygon::draw(){
	if (hidden || spriteIndex < 0 || !image) return;
	if (spriteWidth && spriteHeight) { // Si c'est un sprite et non une image
		GRRLIB_DrawTile(
			getAbsoluteX()+getDrawOrigin().getX(),
			getAbsoluteY()+getDrawOrigin().getY(),
			image,
			getAbsolutePolygonAngle()*180/PI,
			scale,
			scale,
			colorFilter,
			spriteIndex);
	}
	else {
		GRRLIB_DrawImg(
			getAbsoluteX()+getDrawOrigin().getX(),
			getAbsoluteY()+getDrawOrigin().getY(),
			image,
			getAbsolutePolygonAngle()*180/PI,
			scale,
			scale,
			colorFilter);
	}
}

void Polygon::drawDebug() const{
	if (debugHidden) return;
	std::vector<Coordinates> rV = getRotatedVertices();
	float oX = getAbsoluteOriginX();
	float oY = getAbsoluteOriginY();
	float h = ORIGIN_CROSS_HEIGHT;
	float w = ORIGIN_CROSS_WIDTH;
	float a = getAbsoluteAngle();
	float x = oX + radial*cos(a);
	float y = oY + radial*sin(a);

	// Le squelette
	for(int i=0, j, size=rV.size();i<size;i++){
		j = i+1;
		if (j == size) j = 0;
		GRRLIB_Line(rV[i].getX()*scale+x,rV[i].getY()*scale+y,rV[j].getX()*scale+x,rV[j].getY()*scale+y,RED);
	}

	// Le rayon
	GRRLIB_Line(oX,oY,x,y,RED);

	// L'origine
	GRRLIB_Line(oX-w,oY-h,oX+w,oY+h,WHITE);
	GRRLIB_Line(oX+w,oY-h,oX-w,oY+h,WHITE);

	// La nouvelle origine
	GRRLIB_Line(x-w,y-h,x+w,y+h,WHITE);
	GRRLIB_Line(x+w,y-h,x-w,y+h,WHITE);
}

void Polygon::hide(){
	hidden = true;
}

void Polygon::show(){
	hidden = false;
}

bool Polygon::intersect(Polygon* polygon) const{
	std::vector<Coordinates> v1 = getRotatedVertices();
	std::vector<Coordinates> v2 = polygon->getRotatedVertices();
	float x = getAbsoluteX(),y = getAbsoluteY(),xp = polygon->getAbsoluteX(),yp = polygon->getAbsoluteY();
	for (int i=0,k1,size=v1.size();i<size;i++){
		k1 = i+1;
		if (k1 == size) k1 = 0;
		for (int j=0,k2,size2=v2.size();j<size2;j++){
			k2 = j+1;
			if (k2 == size2) k2 = 0;
			if (segmentIntersect(v1[i].getX()+x,v1[i].getY()+y,v1[k1].getX()+x,v1[k1].getY()+y,
				v2[j].getX()+xp,v2[j].getY()+yp,v2[k2].getX()+xp,v2[k2].getY()+yp)) return true;
		}
	}
	return false;
}

bool Polygon::intersect(Coordinates a, Coordinates b) const{
	std::vector<Coordinates> v = getRotatedVertices();
	float x = getAbsoluteX(),y = getAbsoluteY();
	for (int i=0,k1,size=v.size();i<size;i++){
		k1 = i+1;
		if (k1 == size) k1 = 0;
		if (segmentIntersect(v[i].getX()+x,v[i].getY()+y,v[k1].getX()+x,v[k1].getY()+y,
				a.getX(),a.getY(),b.getX(),b.getY())) return true;
	}
	return false;
}

}
