#include "HealthBoost.h"

void HealthBoost::hpBoostMovement(bool& moveHp, float& yHp, float& deltaTimeSeconds, glm::ivec2& res, glm::mat3& matrixHp,
	float& xHp, bool& dissHp) {
	matrixHp = glm::mat3(1);
	if (!moveHp) {
		yHp -= 0.3f * deltaTimeSeconds * res.y;
		matrixHp *= Transform2D::Translate(xHp, yHp);

		if (yHp <= 0) {
			moveHp = true;
		}
	}
	else {
		yHp += 0.3f * deltaTimeSeconds * res.y;
		matrixHp *= Transform2D::Translate(xHp, yHp);

		if (yHp > res.y) {
			if (dissHp != true) {
				moveHp = false;
			}
		}
	}
}

void HealthBoost::collisionHpCalc(float& distXHp, float& distYHp, float& xHp, float& yHp, float& arrowTipInitX,
	float& arrowTipInitY, float& distHp, glm::ivec2& res, int& hpSize, int& collisionHp, int& lifes, bool& dissHp) {
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

void HealthBoost::renderHealth(int &i, int &lifes, glm::mat3 *matrixHealth, float *xHealth, glm::ivec2 &res){
	matrixHealth[i] = glm::mat3(1);
	matrixHealth[i] *= Transform2D::Translate(xHealth[i], res.y - 40);
}