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
	bool isAStrengthSolution;
	float computedStrength;
	std::vector<float> computedOriginX;
public:
	IA(Player* const player);
	~IA();
	void compute();
	void draw() const;
protected:
	void getCloserToTheOpponent();
	void drawTrajectory(
			const float strength,
			const Coordinates& origin,
			const float angle,
			const Color color) const;
	void calculateStrength();
	void calculateAngle(const float strength);
	void calculatePosition(const float strength);
	bool isCollidingWithOpponent(const float strength, float angle);
};

}

#endif /* IA_H_ */
