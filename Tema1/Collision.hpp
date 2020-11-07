#pragma once
#include "Tema1.h"

void collisionStopCalc(float &distXStop, float &distYStop, float &xStop, float &yStop, float &arrowTipInitX,
	float &arrowTipInitY, float &distStop, glm::ivec2 &res, int &stopSize, int &collisionStop, int &lifes) {

	// coliziune stop sign - sageata
	distXStop = arrowTipInitX - xStop;
	distYStop = arrowTipInitY - yStop + res.y / 2;
	distStop = sqrt((distXStop * distXStop) + (distYStop * distYStop));

	if (distStop <= stopSize) {
		collisionStop = 1;
		lifes = 0;
	}
}

void collisionHpCalc(float& distXHp, float& distYHp, float& xHp, float& yHp, float& arrowTipInitX,
	float& arrowTipInitY, float& distHp, glm::ivec2& res, int& hpSize, int& collisionHp, int& lifes, bool &dissHp) {
	distXHp = arrowTipInitX - xHp;
	distYHp = arrowTipInitY - yHp + res.y / 2;
	distHp = sqrt((distXHp * distXHp) + (distYHp * distYHp));

	if (distHp <= hpSize) {
		collisionHp = 1;
		dissHp = true;
		yHp = res.y * 1.1f;
		if (lifes < 10) {
			lifes++;
		}
	}
}
