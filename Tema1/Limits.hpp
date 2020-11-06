#pragma once

void setLimitsPower(bool &arrowShot, float &powerArrow, float &scaleXPowerBar) {
	if (arrowShot == false) {

		// am setat limite la putere
		powerArrow += 0.3f;
		if (powerArrow >= 40.f) {
			powerArrow = 40.f;
		}

		// limita pentru dreptunghiul de afiseaza powerbar-ul
		scaleXPowerBar += 0.007f;
		if (scaleXPowerBar >= 1.13) {
			scaleXPowerBar = 1.13;
		}
	}
}

void setLimitsArrow(float& xArrow, float& yArrow, glm::ivec2& res, bool& leftClick,
	bool& arrowShot, float& powerArrow, float& scaleXPowerBar) {

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

void BowMoveUpDown(int &moveBow, float &yBow, int &bowSize, int &border, glm::ivec2 &res) {
	// miscare W,S || W = 0 , S = 1
	if (moveBow == 0) {

		// pun o margine astfel incat arcul sa nu iasa din rezolutia superioara
		if (yBow + (res.y / 2) > res.y - bowSize - border) {
			moveBow = -1;
		}
		else {
			// daca e ok in plan, muta arcul pe axa Oy in sus
			yBow += 2.f;
			moveBow = -1;
		}
	}
	else if (moveBow == 1) {

		// pun o margine astfel incat arcul sa nu iasa din rezolutia inferioara
		if (yBow + (res.y / 2) < bowSize + border) {
			moveBow = -1;
		}
		else {
			// daca e ok in plan, muta arcul pe axa Oy in jos
			yBow -= 2.f;
			moveBow = -1;
		}
	}
}