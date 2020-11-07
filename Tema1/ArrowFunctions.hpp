#pragma once
#include "Tema1.h"
#include "Transform2D.h"

void arrowNotShot(glm::mat3 &matrixArrow, float &yBow, float &angularBow, float &yArrow,
	float &arrowTipInitY, float &arrowTipInitX) {
	// nu a fost sageata trasa, miscare normala
	matrixArrow *= Transform2D::Translate(0, yBow);
	matrixArrow *= Transform2D::Rotate(angularBow);
	yArrow = yBow;
	arrowTipInitY = yBow;
	arrowTipInitX = 0;
}

void arrowShotDirection(bool &arrowShot, float &xArrow, float &yArrow, float &powerArrow, float &deltaTimeSeconds,
	float &lastArrowAngle, float &radToGrade, float &arrowTipInitX, float &arrowTipInitY, glm::mat3 &matrixArrow) {
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

void updateAngleArrow(bool &arrowShot, float &lastArrowAngle, float &angularBow) {
	if (arrowShot == false) {
		lastArrowAngle = angularBow;
		// salvez ultimul angle pentru a-l da la sageata in miscare
	}
}