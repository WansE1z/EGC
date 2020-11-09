#pragma once
#include <iostream>
#include <include/glm.h>
using namespace std;

namespace GameMechanics {
	void secondsHpInc(int& secondsHp, bool& dissHp);
	void updateDifficutly(int& score, int& nrBal, int& nrSh);
	void addScoreBalloons(string balloonColor[3], int& score, int i);
	void PrintFinish(int& lifes, int& score);
	void PrintScore(int& seconds, int& score);
	void Intro();
	void MouseXLimits(int& mouseX, glm::ivec2& res);
	float calculateAngle(int& mouseX, int& mouseY, float& yBow, glm::ivec2& res, float &angularBow, int &mouseYFinal);
}