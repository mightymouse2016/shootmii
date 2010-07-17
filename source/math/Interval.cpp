#include "../tools/Tools.h"
#include "Interval.h"

namespace shootmii{

Interval::Interval(
		const float x1,
		const float x2) :
		minimum(min(x1,x2)),
		maximum(max(x1,x2))
{

}

float Interval::getMin() const{
	return minimum;
}

float Interval::getMax() const{
	return maximum;
}

bool Interval::intersect(Interval& i) const{
	if (minimum <= i.getMin() && i.getMin() <= maximum) return true;
	if (minimum <= i.getMax() && i.getMax() <= maximum) return true;
	if (i.getMin() <= minimum && minimum <= i.getMax()) return true;
	if (i.getMin() <= maximum && maximum <= i.getMax()) return true;
	return false;
}

}
