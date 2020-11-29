#include "Sphere.h"

void SphereFunc::fallingSphere(Sphere& sphere, bool& outsideOfMap, bool& firstPerson, MyCamera* camera, bool &fallen) {
	if (outsideOfMap) {
		if (firstPerson) {
			camera->position.y -= 0.1f;
		}
		sphere.poz.y -= 0.1f;
		fallen = true;
	}
	if (sphere.poz.y <= -6.f) {
		exit(-1);
	}
}

void SphereFunc::jumpSphere(bool& jump, int& seconds, bool &jumping, bool &firstPerson, MyCamera *camera, Sphere &sphere, Gas &gas) {
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
				camera->position.y -= 0.01f;
				gas.poz.y -= 0.01f;
			}
			sphere.poz.y -= 0.01f;
		}
		if (seconds % 100 == 0) {
			jumping = true;
			seconds = 1;
		}
		if (sphere.poz.y <= 0.599f) {
			// readuc coordonatele la normal, incluzand camera
			jumping = false;
			jump = false;
			sphere.poz.y = 0.6f;
			camera->position.y = 1;
			gas.poz.y = 3;
		}
		sphere.poz.z -= 0.1f;
		gas.poz.z -= 0.1f;
		camera->TranslateForward(0.1f);
	}
}