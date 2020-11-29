#pragma once
#include "Sphere.h"
#include "Plank.h"

namespace Detection {
	void detectOutOfMap(Sphere sphere, Plank* invizPlank, bool& outsideOfMap, int& nrPlanks);
	void changeColorWhenTouched(Sphere sphere, Plank* plank2, bool& outsideOfMap, int& nrPlanks);
	void changeColorWhenTouchedFirstCol(Sphere sphere, Plank* plank, bool& outsideOfMap, int& nrPlanks);
}
