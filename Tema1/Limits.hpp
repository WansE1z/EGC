#pragma once
#include <iostream>
using namespace std;

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

	// daca vrem sa nu stam mult dupa sageata, poate sa fie comentat
	if (powerArrow <= 3.f) {
		if (xArrow >= res.x * 0.35f) {
			xArrow = 0;
			leftClick = false;
			arrowShot = false;
			powerArrow = 0;
			scaleXPowerBar = 0.2f;
		}
	}

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

void secondsHpInc(int &secondsHp, bool &dissHp) {
	secondsHp++; // secondsHp initial este 502, ca sa nu fie % 500 == 1 instant
	if (secondsHp % 500 == 1) {
		/* logica este in felul urmator, este un timer
		atunci cand se respecta cerinta, inseamna ca a trecut destul timp
		nu vreau ca jocul sa ofere posibilitatea de vieti foarte multe, asa ca introduc acest timer
		tinta este mica, sa fie greu sa iei viata */
		secondsHp = 0;
		dissHp = false;
	}
}