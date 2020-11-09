#include "Balloon.h"
#include "GameMechanics.h"

void Balloon::balloonMovementAndDissapear(int& i, glm::mat3* matrixBalloon, float *xBal, float *yBal, float &deltaTimeSeconds,
	glm::ivec2 &res, int *collisionBal, bool *dissapearedBal) {
	matrixBalloon[i] = glm::mat3(1);
	matrixBalloon[i] *= Transform2D::Translate(xBal[i], -10);
	// pozitia initiala pe ecran

	yBal[i] += 0.2f * deltaTimeSeconds * res.y;
	matrixBalloon[i] *= Transform2D::Translate(0, yBal[i]);
	// miscarea "in sus" a balonului

	// daca exista coliziune, dispare balonul
	if (collisionBal[i] == 1) {
		matrixBalloon[i] *= Transform2D::Scale(0, 0);
		collisionBal[i] = 0;
		dissapearedBal[i] = true;
	}

	// readucerea in pozitie cand iese de pe axa oy a scenei
	// daca balonul a fost lovit, cand revine pe ecran sa reapara
	if (yBal[i] >= (res.y * 1.1f)) {
		if (dissapearedBal[i] == true) {
			dissapearedBal[i] = false;
		}
		yBal[i] = -10;
		xBal[i] = rand() % (res.x - 200) + 150;
	}
}

void Balloon::checkCollisionBalloon(int &nrBal, float *distxBal, float *distyBal, float *distBal, float &arrowTipInitX, float &arrowTipInitY,
	float *xBal, float *yBal, glm::ivec2 &res, int &balloonSize, int *collisionBal, std::string *balloonColor, int &score) {
	for (int i = 0; i < nrBal; i++) {
		distxBal[i] = arrowTipInitX - xBal[i];
		distyBal[i] = arrowTipInitY - yBal[i] + res.y / 2 + balloonSize + 4;
		distBal[i] = sqrt((distxBal[i] * distxBal[i]) + (distyBal[i] * distyBal[i]));
		if (distBal[i] <= balloonSize) {
			collisionBal[i] = 1;
			yBal[i] = 1.1f * res.y;
			// formula punct-cerc, a avut loc coliziune

			// adun scor de la baloane (balon ROSU -> 100 / GALBEN -> -50)
			GameMechanics::addScoreBalloons(balloonColor, score, i);
		}
	}
}
