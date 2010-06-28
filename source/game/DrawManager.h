#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

#include <list>
#include <set>

namespace shootmii{

class Polygon;
class Ammo;
class Bonus;
class Animation;

class ComparePolygons{
public:
	bool operator()(Polygon* p1,Polygon* p2);
};

class DrawManager {
private:
	std::multiset<Polygon*, ComparePolygons>* polygonsToDraw;
public:
	DrawManager();
	~DrawManager();
	void addToDraw(Polygon* polygon);
	void addToDraw(std::list<Ammo*>* ammosList);
	void addToDraw(std::list<Bonus*>* bonusesList);
	void addToDraw(std::list<Animation*>* animationsList);
	void draw();
};

}

#endif /* DRAWMANAGER_H_ */
