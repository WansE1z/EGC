#include "Shuriken.h"

void Shuriken::shurikenMovementAndDissapear(int &i, glm::mat3 *matrixSh, glm::ivec2 &res, float *xSh, float *ySh,
	float &deltaTimeSeconds, int *collisionSh, int *collisionBow, bool *dissapearedSh, float &angularStep) {
	matrixSh[i] = glm::mat3(1);
	matrixSh[i] *= Transform2D::Translate(res.x, ySh[i]);

	// valoare de se scade mereu din x, ca sa mearga pe orizontala invers
	xSh[i] -= 0.2f * deltaTimeSeconds * res.x;
	matrixSh[i] *= Transform2D::Translate(xSh[i], 0);

	// daca exista coliziune intre sageata-shuriken sau arc-shuriken, acesta dispare
	if (collisionSh[i] == 1 || collisionBow[i] == 1) {
		matrixSh[i] *= Transform2D::Scale(0, 0);
		collisionSh[i] = 0;
		collisionBow[i] = 0;
		dissapearedSh[i] = true;
	}

	// daca iese din ecran, sa revina
	if (xSh[i] < -res.x * 1.1f) {
		if (dissapearedSh[i] == true) {
			dissapearedSh[i] = false;
		}
		xSh[i] = res.x * 0.1f;
		ySh[i] = rand() % (res.y - 200) + 100;
	}

	// sa se invarta in timp ce se misca pe orizontala
	matrixSh[i] *= Transform2D::Rotate(angularStep);
}

void Shuriken::checkCollisionShuriken(int &nrSh, float *distxSh, float *distySh, float *distSh, float &arrowTipInitX,
	float &arrowTipInitY, glm::ivec2 &res, float *xSh, float *ySh, int &shurikenSize, int *collisionSh, int &score) {
	for (int i = 0; i < nrSh; i++) {
		distxSh[i] = arrowTipInitX - res.x - xSh[i];
		distySh[i] = arrowTipInitY - ySh[i] + res.y / 2;
		distSh[i] = sqrt((distxSh[i] * distxSh[i]) + (distySh[i] * distySh[i]));
		if (distSh[i] <= shurikenSize * sqrt(2)) {
			collisionSh[i] = 1;
			xSh[i] = -res.x * 1.1f;
			// formula punct-cerc, a avut loc coliziune

			score += 200;
			cout << "You hit a shuriken! +200 SCORE" << endl;
		}
	}
}