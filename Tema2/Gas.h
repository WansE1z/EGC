#pragma once
#include <include\glm.h>
#include <iostream>
using namespace std;

class Gas {
	public:
		glm::vec3 poz;
		float fuel;

};

namespace GasFunc {
	void outOfFuel(Gas& gas);
}