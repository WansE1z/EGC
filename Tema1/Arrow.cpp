#include "Arrow.h"

void Arrow::setLimitsArrow(float& xArrow, float& yArrow, glm::ivec2& res, bool& leftClick,
	bool& arrowShot, float& powerArrow, float& scaleXPowerBar) {

	// daca vrem sa stam mult dupa sageata, poate sa fie comentat

	if (powerArrow >= 3.f && powerArrow <= 10.f) {
		if (xArrow >= res.x * 3 / 4) {
			xArrow = 0;
			leftClick = false;
			arrowShot = false;
			powerArrow = 0;
			scaleXPowerBar = 0.2f;
		}
	}

	// verificare sa nu iasa din window
	if (xArrow >= res.x || yArrow >= res.y || yArrow <= -res.y) {
		if (yArrow >= res.y || yArrow <= -res.y) {
			yArrow = 0;
		}
		xArrow = 0;
		leftClick = false;
		arrowShot = false;
		powerArrow = 0;
		scaleXPowerBar = 0.2f;
	}
}

void Arrow::arrowNotShot(glm::mat3& matrixArrow, float& yBow, float& angularBow, float& yArrow,
	float& arrowTipInitY, float& arrowTipInitX) {
	// nu a fost sageata trasa, miscare normala
	matrixArrow *= Transform2D::Translate(0, yBow);
	matrixArrow *= Transform2D::Rotate(angularBow);
	yArrow = yBow;
	arrowTipInitY = yBow;
	arrowTipInitX = 0;
}

void Arrow::arrowShotDirection(bool& arrowShot, float& xArrow, float& yArrow, float& powerArrow, float& deltaTimeSeconds,
	float& lastArrowAngle, float& radToGrade, float& arrowTipInitX, float& arrowTipInitY, glm::mat3& matrixArrow) {
	arrowShot = true;
	// arrow-ul a fost lansat

	xArrow += powerArrow * deltaTimeSeconds * cos(lastArrowAngle) * radToGrade;
	yArrow += powerArrow * deltaTimeSeconds * sin(lastArrowAngle) * radToGrade;
	// mentin directia

	arrowTipInitX += powerArrow * deltaTimeSeconds * cos(lastArrowAngle) * radToGrade;
	arrowTipInitY += powerArrow * deltaTimeSeconds * sin(lastArrowAngle) * radToGrade;

	matrixArrow *= Transform2D::Translate(xArrow, yArrow);
	matrixArrow *= Transform2D::Rotate(lastArrowAngle);
}

void Arrow::updateAngleArrow(bool& arrowShot, float& lastArrowAngle, float& angularBow) {
	if (arrowShot == false) {
		lastArrowAngle = angularBow;
		// salvez ultimul angle pentru a-l da la sageata in miscare
	}
}

void Arrow::setLimitsPower(bool& arrowShot, float& powerArrow, float& scaleXPowerBar) {
	if (arrowShot == false) {

		// am setat limite la putere
		powerArrow += 2.f;
		if (powerArrow >= 60.f) {
			powerArrow = 60.f;
		}

		// limita pentru dreptunghiul de afiseaza powerbar-ul
		scaleXPowerBar += 0.033f;
		if (scaleXPowerBar >= 1.2) {
			scaleXPowerBar = 1.2;
		}
	}
}