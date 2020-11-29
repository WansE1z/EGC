#pragma once
#include "../../include/glm.h"
#include "Sphere.h"
#include "LabCamera.h"
#include "Gas.h"

using namespace std;

class Plank {
public:
	glm::vec3 poz;
	glm::vec3 pozFin;
	string color;
	string initColor;
	int counter = 0;
	bool giveGas;
	bool loseGas;
	bool gaveGas;
	bool lostGas;
	bool endGame;
	bool giveSpeed;
	bool gaveSpeed;
};

namespace PlankFunc {
	void initPlanks(Plank* plank, Plank* plank2, Plank* invizPlank, int& nrPlanks, int& random, int& random2, int& random3);
	void planksOutOfVision(int& nrPlanks, MyCamera* camera, Plank* plank, Plank* plank2, Plank* invizPlank);
	void powerupsPlank(Plank* plank2, Plank* plank, Gas& gas, bool& speedy, int& i, bool& gasMod);
}