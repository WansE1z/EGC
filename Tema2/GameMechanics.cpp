#include "GameMechanics.h"

void GameMechanics::timeForSpeedPowerup(bool &speedy, int &secondsSpeed) {
	if (speedy) {
		secondsSpeed++;
		if (secondsSpeed % 200 == 0) {
			speedy = false;
		}
	}
}

void GameMechanics::movementCameraObjects(Sphere& sphere, Gas& gas, float &deltaTimeSeconds, float &speed, MyCamera* camera) {
	float cameraSpeed = 5.0f;
	sphere.poz.z -= deltaTimeSeconds * speed * cameraSpeed;
	gas.poz.z -= deltaTimeSeconds * speed * cameraSpeed;
	camera->TranslateForward(deltaTimeSeconds * cameraSpeed * speed);
}

void GameMechanics::changeSpeed(bool &speedy, int& secondsSpeed, float &speed, WindowObject* window) {
	if (!speedy) {
		// speed is between 1.f and 4f
		// if there is the powerup going, the speed is 10.f
		secondsSpeed = 1;
		if (speed == 10.f) {
			speed = 4.f;
		}
		if (window->KeyHold(GLFW_KEY_W)) {
			if (speed < 4.f) {
				speed += 0.1f;
			}
			if (speed >= 4.f) {
				speed = 4.f;
			}
		}
		if (window->KeyHold(GLFW_KEY_S)) {
			if (speed > 1.f) {
				speed -= 0.1f;
			}
			if (speed <= 1.f) {
				speed = 1.f;
			}
		}
	}
	else {
		speed = 10.f;
	}
}

void GameMechanics::jumpAD(bool &fallen, WindowObject* window, Sphere& sphere, bool &firstPerson, MyCamera* camera, Gas& gas, bool &jump) {
	if (!fallen) {
		if (window->KeyHold(GLFW_KEY_A)) {
			if (sphere.poz.x != -7.5f) {
				sphere.poz.x -= 7.f;
				// scadem din pozitia sferei
				if (firstPerson) {
					camera->position.x -= 7.f;
					gas.poz.x -= 7.f;
					// daca este first person, trebuie sa scadem si x-ul camerei, sa urmareasca sfera
				}
			}
		}
		if (window->KeyHold(GLFW_KEY_D)) {
			if (sphere.poz.x != 6.5f) {
				sphere.poz.x += 7.f;
				if (firstPerson) {
					camera->position.x += 7.f;
					gas.poz.x += 7.f;
					// daca este first person, trebuie sa crestem si x-ul camerei, sa urmareasca sfera
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_SPACE)) {
			jump = true;
		}
	}
}

void GameMechanics::toggleFirstPersonOrThirdPerson(int& key, bool &firstPerson, MyCamera* camera, Sphere& sphere, Gas& gas) {
	if (key == GLFW_KEY_C)
	{
		firstPerson = !firstPerson;
		// schimbare intre first si third person
		if (firstPerson) {
			camera->position.z -= 14;
			// modific z-ul sa fie de mai aproape 

			camera->position.x = sphere.poz.x;
			// x-ul camerei trebuie sa urmareasca x-ul sferei

			gas.poz.z -= 14;
			// face parte din ui, tb setat la fel ca camera

			gas.poz.x = sphere.poz.x + 4;
		}
		else {
			camera->position.z += 14;
			// readuc z-ul la normal (third person)

			camera->position.x = 0;
			// x-ul devine 0, camera trebuie sa fie centrata

			gas.poz.z += 14;
			// face parte din ui

			gas.poz.x = 4;
		}
	}
}

void GameMechanics::timeForGasPowerup(bool &gasMod, int& secondsGas) {
	if (gasMod) {
		secondsGas++;
		if (secondsGas % 200 == 0) {
			gasMod = false;
		}
	}
}