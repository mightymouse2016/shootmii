#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "GRRLIB.h"
#include "Coordinates.h"

namespace shootmii{

class Segment {
protected:
	Coordinates a;
	Coordinates b;
public:
	Segment(const Coordinates& a, const Coordinates& b);
	Segment(const float xA, const float yA, const float xB, const float yB);
	const Coordinates& getA() const;
	Coordinates& getA();
	const Coordinates& getB() const;
	Coordinates& getB();
	bool intersect(const Segment& s) const;
	void draw() const;
};

}

#endif /* SEGMENT_H_ */
