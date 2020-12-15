#include "Detection.h"
#include <iostream>


void Detection::detectOutOfMap(Sphere sphere, Plank* invizPlank, bool &outsideOfMap, int &nrPlanks) {
	// parcurg toate platformele
	// invizPlank reprezinta niste platforme care nu sunt randate, de unde le si numesc "invizibile"
	// m-am gandit ca daca vor fi atinse aceste platforme, inseamna ca este in afara scenei
	// nu am folosit formula coliziunii din enunt pentru ca eu detectez doar daca partea de jos a sferei atinge platforma
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
					// daca platforma e rosie
					if (plank2[i].color == "red") {
						plank2[i].endGame = true;
					}

					// daca platforma e galbena
					if (plank2[i].lostGas != true) {
						if (plank2[i].color == "yellow") {
							plank2[i].loseGas = true;
							plank2[i].lostGas = true;
						}
					}
					// fac platforma mov, pentru ca a fost atinsa si nu este in afara hartii
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

					// platforma verde
					if (plank[i].gaveGas != true) {
						if (plank[i].color == "green") {
							plank[i].giveGas = true;
							plank[i].gaveGas = true;
						}
					}

					// platforma orange
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