#include "../ShootMii.h"

namespace shootmii {

bool intervalIntersect(const float MA1,const float MA2,const float MB1,const float MB2){
	float m = min(MA1,MA2), M = max(MA1,MA2);
	return ((MB1 >= m && MB1 <= M) || (MB2 >= m && MB2 <= M));
}

bool segmentIntersect(Coordinates A, Coordinates B, Coordinates C, Coordinates D){
	//return (intervalIntersect(a.getX(),A.getX(),b.getX(),B.getX()) && intervalIntersect(a.getY(),A.getY(),b.getY(),B.getY()));
	float Ax = A.getX(), Bx = B.getX(), Cx = C.getX(), Dx = D.getX();
	float Ay = A.getY(), By = B.getY(), Cy = C.getY(), Dy = D.getY();
	float r = ((Ay-Cy)*(Dx-Cx)-(Ax-Cx)*(Dy-Cy))/((Bx-Ax)*(Dy-Cy)-(By-Ay)*(Dx-Cx));
	float s = ((Ay-Cy)*(Bx-Ax)-(Ax-Cx)*(By-Ay))/((Bx-Ax)*(Dy-Cy)-(By-Ay)*(Dx-Cx));
	if (0 <= r && r <= 1 && 0 <= s && s <= 1) return true;
	return false;
}

Polygon::Polygon(
	const float _originX,
	const float _originY,
	const float _radial,
	const float _angle,
	const float _polygonAngle,
	const float _spin,
	Polygon* _father,
	Coordinates _drawOrigin,
	GRRLIB_texImg* _image,
	const int _spriteIndex,
	const int _spriteWidth,
	const int _spriteHeight) :
		originX(_originX),
		originY(_originY),
		radial(_radial),
		spin(_spin),
		angle(_angle),
		polygonAngle(_polygonAngle),
		father(_father),
		drawOrigin(_drawOrigin),
		image(_image),
		spriteIndex(_spriteIndex),
		spriteWidth(_spriteWidth),
		spriteHeight(_spriteHeight)
{
	if (spriteWidth && spriteHeight) { // Si c'est un sprite et non une image
		GRRLIB_InitTileSet(image, spriteWidth, spriteHeight, 0);
	}
}

Polygon::~Polygon(){
	children.clear();
}

const vector<Coordinates>& Polygon::getVertices() const{
	return vertices;
}

vector<Coordinates> Polygon::getRotatedVertices() const{
	float verticeAngle;
	float verticeRadial;
	vector<Coordinates> rotatedVertices;
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
	return Coordinates(drawOriginRadial*cos(angle*spin+polygonAngle+drawOriginAngle),drawOriginRadial*sin(angle*spin+polygonAngle+drawOriginAngle));
}

float Polygon::getOriginX() const{
	return originX;
}

float Polygon::getOriginY() const{
	return originY;
}

float Polygon::getAbsoluteOriginX() const{
	if (father) return father->getAbsoluteX()
		+ originX*cos(father->getAbsolutePolygonAngle())
		+ originY*sin(father->getAbsolutePolygonAngle());
	return originX;
}

float Polygon::getAbsoluteOriginY() const{
	if (father) return father->getAbsoluteY()
		+ originX*sin(father->getAbsolutePolygonAngle())
		+ originY*cos(father->getAbsolutePolygonAngle());
	return originY;
}

float Polygon::getX() const{
	return originX + radial*cos(getAbsoluteAngle());
}

float Polygon::getY() const{
	return originY + radial*sin(getAbsoluteAngle());
}

float Polygon::getAbsoluteX() const{
	return getAbsoluteOriginX() + radial*cos(getAbsoluteAngle());
}

float Polygon::getAbsoluteY() const{
	return getAbsoluteOriginY() + radial*sin(getAbsoluteAngle());
}

float Polygon::getRadial() const{
	return radial;
}

float Polygon::getSpin() const{
	return spin;
}
float Polygon::getAngle() const{
	return angle;
}

float  Polygon::getAbsoluteAngle() const{
	if (father) return father->getAbsolutePolygonAngle() + angle;
	return angle;
}

float  Polygon::getPolygonAngle() const{
	return angle*spin + polygonAngle;
}

float  Polygon::getAbsolutePolygonAngle() const{
	if (father) return father->getAbsolutePolygonAngle() + angle*spin + polygonAngle;
	return angle*spin + polygonAngle;
}

Polygon* Polygon::getFather() const{
	return father;
}

void Polygon::setOriginX(const int _originX){
	originX = _originX;
}

void Polygon::setOriginY(const int _originY){
	originY = _originY;
}

void Polygon::setRadial(const float _radial){
	radial = _radial;
}

void Polygon::setSpin(const float _spin){
	spin = _spin;
}

void Polygon::setAngle(const float _angle){
	angle = _angle;
}

void Polygon::setFather(Polygon* _father){
	father = _father;
}

void Polygon::addChild(Polygon * child){
	children.push_back(child);
	child->setFather(this);
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
	int size = vertices.size();
	for(int i=0;i<size;i++) vertices[i].grow(k);
}

void Polygon::draw() const{
	// Les enfants d'abords (pour qu'ils soient � l'arri�re plan)
	for(int i=0,size=children.size();i<size;i++){
		if (children[i]) children[i]->draw();
	}
	if(App::console->isDebug()){
		if (spriteIndex == -1) return;
		// Le mode debug (squelette)
		vector<Coordinates> rotatedVertices = getRotatedVertices();
		int size = rotatedVertices.size();
		for(int i=0,j;i<size;i++){
			if (i+1 == size) j = 0;
			else j = i+1;
			GRRLIB_Line(
				rotatedVertices[i].getX()+getAbsoluteX(),
				rotatedVertices[i].getY()+getAbsoluteY(),
				rotatedVertices[j].getX()+getAbsoluteX(),
				rotatedVertices[j].getY()+getAbsoluteY(),RED);
		}
		// Le rayon
		GRRLIB_Line(getAbsoluteOriginX(),getAbsoluteOriginY(),getAbsoluteX(),getAbsoluteY(),RED);
		// L'origine
		GRRLIB_Line(
			getAbsoluteOriginX()-ORIGIN_CROSS_WIDTH,
			getAbsoluteOriginY()-ORIGIN_CROSS_HEIGHT,
			getAbsoluteOriginX()+ORIGIN_CROSS_WIDTH,
			getAbsoluteOriginY()+ORIGIN_CROSS_HEIGHT,BLACK);
		GRRLIB_Line(
			getAbsoluteOriginX()+ORIGIN_CROSS_WIDTH,
			getAbsoluteOriginY()-ORIGIN_CROSS_HEIGHT,
			getAbsoluteOriginX()-ORIGIN_CROSS_WIDTH,
			getAbsoluteOriginY()+ORIGIN_CROSS_HEIGHT,BLACK);
		// La nouvelle origine
		GRRLIB_Line(
			getAbsoluteX()-ORIGIN_CROSS_WIDTH,
			getAbsoluteY()-ORIGIN_CROSS_HEIGHT,
			getAbsoluteX()+ORIGIN_CROSS_WIDTH,
			getAbsoluteY()+ORIGIN_CROSS_HEIGHT,BLACK);
		GRRLIB_Line(
			getAbsoluteX()+ORIGIN_CROSS_WIDTH,
			getAbsoluteY()-ORIGIN_CROSS_HEIGHT,
			getAbsoluteX()-ORIGIN_CROSS_WIDTH,
			getAbsoluteY()+ORIGIN_CROSS_HEIGHT,BLACK);
	} else {
		// L'objet en lui m�me (image)
		if (spriteWidth && spriteHeight) { // Si c'est un sprite et non une image
			GRRLIB_DrawTile(
				getAbsoluteX()+getDrawOrigin().getX(),
				getAbsoluteY()+getDrawOrigin().getY(),
				*image, getAbsolutePolygonAngle()*180/PI, 1, 1, WHITE, spriteIndex);
		} else {
			GRRLIB_DrawImg(
				getAbsoluteX()+getDrawOrigin().getX(),
				getAbsoluteY()+getDrawOrigin().getY(),
				*image, getAbsolutePolygonAngle()*180/PI, 1, 1, WHITE);
		}
	}
}

bool Polygon::intersect(Polygon* polygon) const{
	for (int i=0,k1,size=vertices.size();i<size;i++){
		if (i == size-1) k1 = 0;
		else k1 = i+1;
		for (int j=0,k2,size2=polygon->getVertices().size();j<size2;j++){
			if (j == size2-1) k2 = 0;
			else k2 = j+1;
			if (segmentIntersect(vertices[i], vertices[k1], vertices[j], vertices[k2])) return true;
		}
	}
	return false;
}

}
