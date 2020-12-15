#pragma once
#include "Sphere.h"
#include "Gas.h"
#include <Core\Window\WindowObject.h>
#include <iostream>
using namespace std;

namespace GameMechanics {
	void introGame();
	void timeForSpeedPowerup(bool& speedy, int& secondsSpeed);
	void movementCameraObjects(Sphere& sphere, Gas& gas, float& deltaTimeSeconds, float& speed, MyCamera* camera);
	void changeSpeed(bool& speedy, int& secondsSpeed, float& speed, WindowObject* window);
	void jumpAD(bool& fallen, WindowObject* window, Sphere& sphere, bool& firstPerson, MyCamera* camera, Gas& gas, bool& jump);
	void toggleFirstPersonOrThirdPerson(int& key, bool& firstPerson, MyCamera* camera, Sphere& sphere, Gas& gas);
	void timeForGasPowerup(bool& gasMod, int& secondsGas);
}