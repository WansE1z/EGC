#pragma once
#include "Tema1.h"
#include "Transform2D.h"

void scaleThePowerBar(glm::mat3& matrixPowerBar,glm::mat3 &matrixPowerBarOut, float& angularBow, float& scaleXPowerBar) {
	matrixPowerBarOut = glm::mat3(1);

	matrixPowerBar *= Transform2D::Rotate(-angularBow);
	// powerbar-ul sa nu se roteasca ca arcul

	matrixPowerBarOut = matrixPowerBar;

	matrixPowerBar *= Transform2D::Scale(scaleXPowerBar, 1.f);
	// scalez powerbar-ul in functie de powerArrow

	matrixPowerBar *= Transform2D::Translate(-600, 1.f);
	matrixPowerBarOut *= Transform2D::Translate(-600, 1.f);
	// sa nu se miste powerbar-ul in dreapta
}

void matrixStopSignUpdate(bool &moveStopSign, float &deltaTimeSeconds, glm::ivec2 &res, float &yStop, 
	glm::mat3 &matrixStop, float &xStop) {
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

void matrixHpUpdate(bool &moveHp, float &yHp, float &deltaTimeSeconds, glm::ivec2 &res, glm::mat3 &matrixHp,
	float &xHp, bool &dissHp) {
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