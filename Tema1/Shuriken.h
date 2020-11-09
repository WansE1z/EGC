#pragma once
#include "Shuriken.h"
#include "Transform2D.h"
#include <iostream>
using namespace std;

namespace Shuriken {
	void shurikenMovementAndDissapear(int& i, glm::mat3* matrixSh, glm::ivec2& res, float* xSh, float* ySh,
		float& deltaTimeSeconds, int* collisionSh, int* collisionBow, bool* dissapearedSh, float& angularStep);

	void checkCollisionShuriken(int& nrSh, float* distxSh, float* distySh, float* distSh, float& arrowTipInitX,
		float& arrowTipInitY, glm::ivec2& res, float* xSh, float* ySh, int& shurikenSize, int* collisionSh, int& score);
}