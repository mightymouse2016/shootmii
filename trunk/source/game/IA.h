#ifndef IA_H_
#define IA_H_

#include <vector>

namespace shootmii {

class Player;

class IA{
protected:
	Player* const player;
	std::vector<float> computedAngles;
	bool isAStrengthSolution;
	float computedStrength;
	std::vector<float> computedOriginX;
public:
	IA(Player* const player);
	void compute();
	void draw() const;
protected:
	void drawTrajectory(
			const float strength,
			const Coordinates& origin,
			const float angle,
			const u32 color) const;
	void calculateStrength();
	void calculateStrength2();
	void calculateAngle(const float strength);
	void calculatePosition(const float strength);
	bool isTargetTooHigh();
	bool isCollidingWithOpponent(const float strength, float angle);
};

}

#endif /* IA_H_ */
