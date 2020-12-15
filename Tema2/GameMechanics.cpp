#include "GameMechanics.h"
void GameMechanics::introGame() {
	cout << "-------------------------------- START OF GAME --------------------------------" << endl;
	cout << "Hello! Scopul jocului este sa reusesti sa rezisti cat mai mult." << endl;
	cout << "Platforma verde iti da combustibil, galbena iti ia din combustibil, portocalia iti mareste viteza pentru o perioada de timp, iar cea rosie te omoara!" << endl;
}

void GameMechanics::timeForSpeedPowerup(bool &speedy, int &secondsSpeed) {
	// speedy e true, daca powerup-ul e activ
	if (speedy) {
		// incrementez acest integer sa imi dau seama cat timp trece
		secondsSpeed++;

		if (secondsSpeed % 400 == 0) {
			// daca au trecut "400 de ms" , iese din powerup si resetez contorul
			speedy = false;
			secondsSpeed = 1;
		}
	}
}

void GameMechanics::movementCameraObjects(Sphere& sphere, Gas& gas, float &deltaTimeSeconds, float &speed, MyCamera* camera) {
	// in aceasta tema trebuie miscate constant 3 obiecte
	// sfera, camera si dreptunghiul
	// eu defapt misc aceste obiecte care teoretic stau
	// dreptunghiul trebuie sa fie pe loc, deci il misc

	float cameraSpeed = 5.0f;
	sphere.poz.z -= deltaTimeSeconds * speed * cameraSpeed;
	gas.poz.z -= deltaTimeSeconds * speed * cameraSpeed;
	camera->TranslateForward(deltaTimeSeconds * cameraSpeed * speed);
}

void GameMechanics::changeSpeed(bool &speedy, int& secondsSpeed, float &speed, WindowObject* window) {
	if (!speedy) {
		// viteza este default intre 1.f si 4.f
		// daca exista power-ul, o sa fie 10.f

		secondsSpeed = 1;
		if (speed == 10.f) {
			speed = 4.f;
		}
		if (window->KeyHold(GLFW_KEY_W)) {
			// sa nu poata depasii mai mult de 4.f
			if (speed < 4.f) {
				speed += 0.1f;
			}
			if (speed >= 4.f) {
				speed = 4.f;
			}
		}
		if (window->KeyHold(GLFW_KEY_S)) {
			// sa nu poate scadea sub 1.f
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
			if (sphere.poz.x != -7.4f) {
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
			if (sphere.poz.x != 6.6f) {
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

			gas.poz.y = 3.7f;
			gas.poz.z -= 14;
			// face parte din ui, tb setat la fel ca camera

			gas.poz.x = sphere.poz.x + 3.65f;
		}
		else {
			camera->position.z += 14;
			// readuc z-ul la normal (third person)

			camera->position.x = -0.25f;
			// x-ul devine 0, camera trebuie sa fie centrata

			gas.poz.y = 3.7f;
			gas.poz.z += 14;
			// face parte din ui

			gas.poz.x = 3.4;
		}
	}
}

void GameMechanics::timeForGasPowerup(bool &gasMod, int& secondsGas) {
	if (gasMod) {
		secondsGas++;
		if (secondsGas % 200 == 0) {
			gasMod = false;
			secondsGas = 1;
		}
	}
}