#pragma once
#include <include/glm.h>
#include <iostream>
using namespace std;

namespace Bow {
	void BowMoveUpDown(int& moveBow, float& yBow, int& bowSize, int& border, glm::ivec2& res);
	void CheckCollisionBow(int& nrSh, glm::ivec2& res, float* distXBow, float* distYBow,
		float& xBow, float& yBow, float* xSh, float* ySh, int& bowSize, float* distBow, int& shurikenSize,
		int* collisionBow, int& lifes);
}