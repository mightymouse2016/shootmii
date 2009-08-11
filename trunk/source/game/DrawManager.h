#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

#include "../ShootMii.h"

namespace shootmii{

class ComparePolygons{
public:
	bool operator()(Polygon* p1,Polygon* p2){
		return (p1->getLayer() < p2->getLayer());
	}
};

class DrawManager {
private:
	multiset<Polygon*, ComparePolygons>* polygonsToDraw;
public:
	DrawManager();
	~DrawManager();
	void addToDraw(Polygon* polygon);
	void addToDraw(list<Ammo*>* ammosList);
	void addToDraw(list<Bonus*>* bonusesList);
	void addToDraw(list<Animation*>* animationsList);
	void draw();
};

}

#endif /* DRAWMANAGER_H_ */
