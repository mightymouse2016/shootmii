#ifndef IA_H_
#define IA_H_

#include <vector>
#include "../tools/Color.h"

namespace shootmii {

class Player;
class Interval;

class IA{
protected:
	Player* const player;
	Interval* computedAngles;
	float* computedStrength;
	bool firing;
public:
	IA(Player* const player);
	~IA();
	void compute();
	void drawDebug() const;
	void init();
protected:
	void getCloserToTheOpponent();
	void drawTrajectory(
			const float strength,
			const Coordinates& origin,
			const float angle,
			const Color color) const;
	float* calculateStrength() const;
	Interval* calculateAngle(const float strength) const;
	bool isCollidingWithOpponent(const float strength, float angle);
};

}

#endif /* IA_H_ */
