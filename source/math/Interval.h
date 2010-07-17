#ifndef INTERVAL_H_
#define INTERVAL_H_

namespace shootmii{

class Interval{
protected:
	float minimum;
	float maximum;
public:
	Interval(const float x1, const float x2);
	float getMin() const;
	float getMax() const;
	bool intersect(Interval& i) const;
};

}

#endif /* INTERVAL_H_ */
