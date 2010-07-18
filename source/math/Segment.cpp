#include "Segment.h"

namespace shootmii{

Segment::Segment(const Coordinates& _a, const Coordinates& _b) :
		a(_a),
		b(_b)
{

}

Segment::Segment(const float xA, const float yA, const float xB, const float yB) :
		a(xA,yA),
		b(xB,yB)
{

}

const Coordinates& Segment::getA() const{
	return a;
}

Coordinates& Segment::getA(){
	return a;
}

const Coordinates& Segment::getB() const{
	return b;
}

Coordinates& Segment::getB(){
	return b;
}

bool Segment::intersect(const Segment& seg) const{
	const float a1x = a.getX(), a1y = a.getY(), b1x = b.getX(), b1y = b.getY();
	const float a2x = seg.getA().getX(), a2y = seg.getA().getY(), b2x = seg.getB().getX(), b2y = seg.getB().getY();
	const float r = ((a1y-a2y)*(b2x-a2x)-(a1x-a2x)*(b2y-a2y))/((b1x-a1x)*(b2y-a2y)-(b1y-a1y)*(b2x-a2x));
	const float s = ((a1y-a2y)*(b1x-a1x)-(a1x-a2x)*(b1y-a1y))/((b1x-a1x)*(b2y-a2y)-(b1y-a1y)*(b2x-a2x));
	if (0 <= r && r <= 1 && 0 <= s && s <= 1) return true;
	return false;
}

}

