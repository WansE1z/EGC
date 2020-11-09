#pragma once
#include "Transform2D.h"

namespace StopSign {
	void stopSignMovement(bool& moveStopSign, float& deltaTimeSeconds, glm::ivec2& res, float& yStop,
		glm::mat3& matrixStop, float& xStop);

	void collisionStopCalc(float& distXStop, float& distYStop, float& xStop, float& yStop, float& arrowTipInitX,
		float& arrowTipInitY, float& distStop, glm::ivec2& res, int& stopSize, int& collisionStop, int& lifes);
}