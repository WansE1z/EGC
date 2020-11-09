#include "Bow.h"

void Bow::BowMoveUpDown(int& moveBow, float& yBow, int& bowSize, int& border, glm::ivec2& res) {
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

void Bow::CheckCollisionBow(int &nrSh, glm::ivec2 &res, float *distXBow, float *distYBow,
	float &xBow, float &yBow, float *xSh, float *ySh, int &bowSize, float *distBow, int &shurikenSize,
	int *collisionBow, int &lifes) {
	for (int i = 0; i < nrSh; i++) {
		distXBow[i] = res.x - xBow + xSh[i] - bowSize / 2;
		distYBow[i] = yBow + res.y / 2 - ySh[i];
		distBow[i] = sqrt((distXBow[i] * distXBow[i]) + (distYBow[i] * distYBow[i]));
		if (distBow[i] <= shurikenSize * sqrt(2) + bowSize) {
			collisionBow[i] = 1;
			xSh[i] = -res.x * 1.1f;
			// x-ul shuriken-ului il fac -res.x * 1.1f, ca sa apara disparut, sa reapara pe ecran

			cout << "The shuriken hit you, you lost a life!" << endl;
			lifes--;
			// daca este coliziune , scad o viata
		}

	}
}