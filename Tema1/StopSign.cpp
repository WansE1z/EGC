#include "StopSign.h"

void StopSign::stopSignMovement(bool& moveStopSign, float& deltaTimeSeconds, glm::ivec2& res, float& yStop,
	glm::mat3& matrixStop, float& xStop) {
	matrixStop = glm::mat3(1);
	if (moveStopSign) {
		yStop += 0.3f * deltaTimeSeconds * res.y;
		matrixStop *= Transform2D::Translate(xStop, yStop);

		if (yStop > res.y) {
			moveStopSign = false;
		}
	}
	else {
		yStop -= 0.3f * deltaTimeSeconds * res.y;
		matrixStop *= Transform2D::Translate(xStop, yStop);

		if (yStop <= 0) {
			moveStopSign = true;
		}
	}
}

void StopSign::collisionStopCalc(float& distXStop, float& distYStop, float& xStop, float& yStop, float& arrowTipInitX,
	float& arrowTipInitY, float& distStop, glm::ivec2& res, int& stopSize, int& collisionStop, int& lifes) {

	// coliziune stop sign - sageata
	distXStop = arrowTipInitX - xStop;
	distYStop = arrowTipInitY - yStop + res.y / 2;
	distStop = sqrt((distXStop * distXStop) + (distYStop * distYStop));

	if (distStop <= stopSize) {
		collisionStop = 1;
		lifes = 0;
	}
}