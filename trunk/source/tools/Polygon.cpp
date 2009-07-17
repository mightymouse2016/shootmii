#include "../ShootMii.h"

namespace shootmii {

Polygon::Polygon(
	const float _originX,
	const float _originY,
	const float _radial,
	const float _angle,
	Polygon* _father) :
		originX(_originX),
		originY(_originY),
		radial(_radial),
		angle(_angle),
		father(_father)
{
	// NOTHING TO DO
}

Polygon::~Polygon(){
	children.clear();
}

const vector<Coordinates>& Polygon::getVertices() const{
	return vertices;
}

vector<Coordinates>* Polygon::getAbsoluteVertices() const{
	int size = vertices.size();
	int x = getAbsoluteX();
	int y = getAbsoluteY();
	int verticeAngle;
	int verticeRadial;
	vector<Coordinates>* absoluteVertices = new vector<Coordinates>;
	absoluteVertices->reserve(size);
	for(int i=0;i<size;i++){
		verticeAngle = vertices[i].getAngle();
		verticeRadial = vertices[i].getRadial();
		absoluteVertices->push_back(Coordinates(x+verticeRadial*cos(angle*spin+verticeAngle),y+verticeRadial*sin(angle*spin+verticeAngle)));
	}
	return absoluteVertices;
}

int Polygon::getOriginX() const{
	return originX;
}

int Polygon::getOriginY() const{
	return originY;
}

int Polygon::getAbsoluteOriginX() const{
	if (father) return father->getAbsoluteX() + originX;
	return originX;
}

int Polygon::getAbsoluteOriginY() const{
	if (father) return father->getAbsoluteY() + originY;
	return originY;
}

int Polygon::getX() const{
	return originX + radial*cos(angle);
}

int Polygon::getY() const{
	return originY + radial*sin(angle);
}

int Polygon::getAbsoluteX() const{
	if (father) return father->getAbsoluteX() + getX();
	return getX();
}

int Polygon::getAbsoluteY() const{
	if (father) return father->getAbsoluteY() + getY();
	return getY();
}

int Polygon::getRadial() const{
	return radial;
}

float Polygon::getSpin() const{
	return spin;
}
float Polygon::getAngle() const{
	return angle;
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
	children.push_front(child);
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
	vector<Coordinates>* verticesRotated = getAbsoluteVertices();
	int size = verticesRotated->size();
	for(int i=0,j;i<size;i++){
		if (i+1 == size) j = 0;
		else j = i+1;
		GRRLIB_Line(
			(*verticesRotated)[i].getX(),
			(*verticesRotated)[i].getY(),
			(*verticesRotated)[j].getX(),
			(*verticesRotated)[j].getY(),RED);
	}
}

}
