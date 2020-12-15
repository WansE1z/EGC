#include "Sphere.h"

void SphereFunc::fallingSphere(Sphere& sphere, bool& outsideOfMap, bool& firstPerson, MyCamera* camera, bool &fallen) {
	// daca este in afara hartii
	if (outsideOfMap) {
		// daca este firstPerson, trebuie sa "cada" si camera
		if (firstPerson) {
			camera->position.y -= 0.1f;
		}
		// scad y-ul sferei pentru efectul caderii
		sphere.poz.y -= 0.1f;

		// acest bool il folosesc pentru ca atunci cand este in cadere, sa nu pot apasa WASD / SPACE
		fallen = true;
	}
	if (sphere.poz.y <= -6.f) {
		cout << "A cazut sfera.. Nu ai fost atent:(" << endl;
		cout << "--------------------------------  END OF GAME  --------------------------------" << endl;
		exit(-1);
	}
}

void SphereFunc::jumpSphere(bool& jump, int& seconds, bool &jumping, bool &firstPerson, MyCamera *camera, Sphere &sphere, Gas &gas) {
	/*
		folosesc doua variabile de tip bool
		jump - sa stiu ca a fost apasata tasta space
		jumping - sa imi dau seama cand este in saritura si cand revine pe "pamant"
		daca este firstPerson, camera trebuie sa urmareasca absolut orice actiune
		daca este thirdPerson, camera nu se misca suplimentar
	*/
	if (jump) {
		seconds++;
		if (!jumping) {
			if (firstPerson) {
				// daca e first person , trebuie sa "sara" si camera
				camera->position.y += 0.01f;
				gas.poz.y += 0.01f;
			}
			sphere.poz.y += 0.01f;
		}
		else {
			if (firstPerson) {
				// daca e first person, trebuie sa "coboare" si camera
				if (camera->position.y > 2.f) {
					camera->position.y -= 0.01f;
					gas.poz.y -= 0.01f;
				}
			}
			sphere.poz.y -= 0.01f;
		}
		if (!firstPerson) {
			camera->position.y = 2.f;
		}
		if (seconds % 100 == 0) {
			// seconds este un contor pentru cat de mult sare
			// teoretic, va fi in saritura 100 ms si in cazatura 100ms
			jumping = true;
			seconds = 1;
		}
		if (sphere.poz.y <= 0.599f) {
			// readuc coordonatele la normal, incluzand camera
			jumping = false;
			jump = false;
			sphere.poz.y = 0.6f;
			camera->position.y = 2;
			gas.poz.y = 3.7f;
		}

		// in timpul sariturii, sfera, camera si dreptunghiul trebuie sa se "miste" in continuare
		sphere.poz.z -= 0.1f;
		gas.poz.z -= 0.1f;
		camera->TranslateForward(0.1f);
	}
}