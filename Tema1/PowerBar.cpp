#include "PowerBar.h"

void PowerBar::scaleThePowerBar(glm::mat3& matrixPowerBar, glm::mat3& matrixPowerBarOut, float& angularBow, float& scaleXPowerBar) {
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