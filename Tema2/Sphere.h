#pragma once
#include "../../include/glm.h"
#include "Plank.h"
#include "LabCamera.h"
#include "Gas.h"

class Sphere {
public:
	glm::vec3 poz;
	glm::vec3 pozFin;
};

namespace SphereFunc {
	void fallingSphere(Sphere& sphere, bool& outsideOfMap, bool& firstPerson, MyCamera* camera, bool& fallen);
	void jumpSphere(bool& jump, int& seconds, bool& jumping, bool& firstPerson, MyCamera* camera, Sphere& sphere, Gas &gas);
}
