#pragma once

#include "Transform2D.h"

namespace HealthBoost {
	void hpBoostMovement(bool& moveHp, float& yHp, float& deltaTimeSeconds, glm::ivec2& res, glm::mat3& matrixHp,
		float& xHp, bool& dissHp);

	void collisionHpCalc(float& distXHp, float& distYHp, float& xHp, float& yHp, float& arrowTipInitX,
		float& arrowTipInitY, float& distHp, glm::ivec2& res, int& hpSize, int& collisionHp, int& lifes, bool& dissHp);

	void renderHealth(int &i, int& lifes, glm::mat3* matrixHealth, float* xHealth, glm::ivec2& res);
}