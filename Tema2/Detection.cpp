#include "Detection.h"
#include <iostream>


void Detection::detectOutOfMap(Sphere sphere, Plank* invizPlank, bool &outsideOfMap, int &nrPlanks) {
	for (int i = 0; i < nrPlanks; i++) {
		if (sphere.poz.x >= invizPlank[i].poz.x && sphere.poz.x <= invizPlank[i].poz.x + 5) {
			if (sphere.poz.z <= invizPlank[i].poz.z && sphere.poz.z >= invizPlank[i].pozFin.z) {
				if (sphere.poz.y == invizPlank[i].poz.y + 0.6f) {
					outsideOfMap = true;
				}
			}
		}
	}
}

void Detection::changeColorWhenTouched(Sphere sphere, Plank* plank2, bool &outsideOfMap, int& nrPlanks) {
	for (int i = 0; i < nrPlanks; i++) {
		if (sphere.poz.x >= plank2[i].poz.x && sphere.poz.x <= plank2[i].poz.x + 5) {
			if (sphere.poz.z <= plank2[i].poz.z && sphere.poz.z >= plank2[i].pozFin.z) {
				if (sphere.poz.y == plank2[i].poz.y + 0.6f) {
					if (plank2[i].color == "red") {
						plank2[i].endGame = true;
					}
					if (plank2[i].lostGas != true) {
						if (plank2[i].color == "yellow") {
							plank2[i].loseGas = true;
							plank2[i].lostGas = true;
						}
					}
					plank2[i].color = "purple";
					outsideOfMap = false;
				}
			}
		}
	}
}

void Detection::changeColorWhenTouchedFirstCol(Sphere sphere, Plank* plank, bool &outsideOfMap, int& nrPlanks) {
	for (int i = 0; i < nrPlanks; i++) {
		if (sphere.poz.x >= plank[i].poz.x && sphere.poz.x <= plank[i].poz.x + 5) {
			if (sphere.poz.z <= plank[i].poz.z && sphere.poz.z >= plank[i].pozFin.z) {
				if (sphere.poz.y == plank[i].poz.y + 0.6f) {
					if (plank[i].gaveGas != true) {
						if (plank[i].color == "green") {
							plank[i].giveGas = true;
							plank[i].gaveGas = true;
						}
					}
					if (plank[i].gaveSpeed != true) {
						if (plank[i].color == "orange") {
							plank[i].giveSpeed = true;
							plank[i].gaveSpeed = true;
						}
					}
					plank[i].color = "purple";
					outsideOfMap = false;
				}
			}
		}
	}
}