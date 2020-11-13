#include "GameMechanics.h"

void GameMechanics::Intro() {
	cout << "Welcome to Bow & Arrow! Your purpose is to hit as many red balloons and shurikens you can. Getting hit by a shuriken will lose you a life, so watch out!" << endl;
	cout << "Beside those items, you can also hit a stop sign, health boost or yellow balloon. The yellow balloon will decrease your score, the stop sign will stop the game, so try not to HIT it! The health boost will give you one more life :) Have fun." << endl;
	cout << "--------------------------------------  START GAME --------------------------------------" << endl;
}



void GameMechanics::MouseXLimits(int& mouseX, glm::ivec2& res)
{
	if (mouseX > res.x) {
		mouseX = res.x;
	}
	else if (mouseX <= 0) {
		mouseX = 0;
	}
}

float GameMechanics::calculateAngle(int& mouseX, int& mouseY, float& yBow, glm::ivec2& res, float& angularBow,
	int& mouseYFinal, WindowObject* window)
{
	mouseX = window->GetCursorPosition().x;
	mouseY = window->GetCursorPosition().y;
	GameMechanics::MouseXLimits(mouseX, res);
	mouseYFinal = -mouseY - yBow + res.y / 2;
	angularBow = glm::atan((float)mouseYFinal / (float)mouseX);
	return angularBow;
}

void GameMechanics::setInitialPositions(float* xBal, float* ySh, glm::ivec2& res, float& xStop, float& yStop, float& xHp, float& yHp, int& cp1, int& cp2)
{
	for (int i = 0; i < 7; i++) {
		xBal[i] = rand() % (res.x - 200) + 150;
		// ox baloane intre 150 si res.x - 200
	}

	for (int i = 0; i < 4; i++) {
		ySh[i] = rand() % (res.y - 200) + 100;
		// oy shuriken-uri intre 100 si res.y - 200
	}

	xStop = rand() % 600 + 300; // 100-700 ox
	yStop = 100;

	yHp = 620;
	xHp = rand() % 600 + 500; // 500-1100 ox

	cp1 = cp2 = rand() % 3;
}

void GameMechanics::holdWSClick(WindowObject* window, bool& arrowShot, float& powerArrow, float& scaleXPowerBar, int& moveBow)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		moveBow = 0;
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			Arrow::setLimitsPower(arrowShot, powerArrow, scaleXPowerBar);
		}
	}

	// daca se tine apasat pe S, se poate tine apasat si click, de aceea maresc si powerArrow-ul
	else if (window->KeyHold(GLFW_KEY_S)) {
		moveBow = 1;
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			Arrow::setLimitsPower(arrowShot, powerArrow, scaleXPowerBar);
		}
	}

	// daca totusi nu tin apasat pe w sau s, pot tine apasat pe click, marind powerArrow-ul
	else if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		Arrow::setLimitsPower(arrowShot, powerArrow, scaleXPowerBar);
	}
}

void GameMechanics::holdMouseUpdate(bool& arrowShot, int& button, bool& leftClick, bool statement)
{
	if (arrowShot == false) {
		if (button == 1) {
			leftClick = statement;
		}
	}
}

void GameMechanics::secondsHpInc(int& secondsHp, bool& dissHp) {
	secondsHp++; // secondsHp initial este 502, ca sa nu fie % 500 == 1 instant
	if (secondsHp % 1000 == 1) {
		/* logica este in felul urmator, este un timer
		atunci cand se respecta cerinta, inseamna ca a trecut destul timp
		nu vreau ca jocul sa ofere posibilitatea de vieti foarte multe, asa ca introduc acest timer
		tinta este mica, sa fie greu sa iei viata */
		secondsHp = 1002;
		dissHp = false;
	}
}

void GameMechanics::updateDifficutly(int& score, int& nrBal, int& nrSh) {
	if (score >= 2000) {
		nrBal = 5;
		nrSh = 3;
	}
	if (score >= 4000) {
		nrBal = 7;
		nrSh = 4;
	}
}

void GameMechanics::addScoreBalloons(string balloonColor[3], int& score, int i) {
	if (balloonColor[i] == "red") {
		score += 100;
		cout << "You popped a red balloon! +100 SCORE" << endl;
	}
	else if (balloonColor[i] == "yellow") {
		score -= 50;
		cout << "You popped a yellow balloon... -50 SCORE" << endl;
	}
}

void GameMechanics::PrintFinish(int& lifes, int& score) {
	if (lifes == 0) {
		cout << "-------------------------------------- END OF GAME --------------------------------------" << endl;
		cout << "You have lost all of your lifes" << endl;
		cout << endl;
		cout << "--------------------------------------    SCORE    --------------------------------------" << endl;
		cout << "The game was finished with the score: " << score;
		cout << endl;
		exit(0);
	}
}

void GameMechanics::PrintScore(int& seconds, int& score) {
	seconds++;
	if (seconds % 500 == 0) {
		cout << "The score right now is : " << score << endl;
	}
}