#pragma once
#include "Transform2D.h"

namespace Balloon {
	void balloonMovementAndDissapear(int& i, glm::mat3* matrixBalloon, float* xBal, float* yBal, float& deltaTimeSeconds,
		glm::ivec2& res, int* collisionBal, bool* dissapearedBal);
	void checkCollisionBalloon(int& nrBal, float* distxBal, float* distyBal, float* distBal, float& arrowTipInitX, float& arrowTipInitY,
		float* xBal, float* yBal, glm::ivec2& res, int& balloonSize, int* collisionBal, std::string* balloonColor, int& score);
}