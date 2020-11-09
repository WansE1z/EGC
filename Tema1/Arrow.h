#pragma once
#include "Transform2D.h"
#include <iostream>

namespace Arrow {

	void setLimitsArrow(float& xArrow, float& yArrow, glm::ivec2& res, bool& leftClick,
		bool& arrowShot, float& powerArrow, float& scaleXPowerBar);

	void arrowNotShot(glm::mat3& matrixArrow, float& yBow, float& angularBow, float& yArrow,
		float& arrowTipInitY, float& arrowTipInitX);

	void arrowShotDirection(bool& arrowShot, float& xArrow, float& yArrow, float& powerArrow, float& deltaTimeSeconds,
		float& lastArrowAngle, float& radToGrade, float& arrowTipInitX, float& arrowTipInitY, glm::mat3& matrixArrow);

	void updateAngleArrow(bool& arrowShot, float& lastArrowAngle, float& angularBow);

	void setLimitsPower(bool& arrowShot, float& powerArrow, float& scaleXPowerBar);
}
