#pragma once
#include <include/glm.h>
#include <iostream>
#include "Transform2D.h"
using namespace std;

namespace Bow {
	void BowMoveUpDown(int& moveBow, float& yBow, int& bowSize, int& border, glm::ivec2& res, 
		glm::mat3& matrixBow, glm::mat3& matrixArrow, glm::mat3& matrixPowerBar, float& angularBow);
	void CheckCollisionBow(int& nrSh, glm::ivec2& res, float* distXBow, float* distYBow,
		float& xBow, float& yBow, float* xSh, float* ySh, int& bowSize, float* distBow, int& shurikenSize,
		int* collisionBow, int& lifes);
}