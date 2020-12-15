#include "Plank.h"

void PlankFunc::initPlanks(Plank* plank, Plank* plank2, Plank* invizPlank, int& nrPlanks, int& random, int& random2, int& random3) {
	for (int i = 0; i < nrPlanks; i++) {

		// culoarea initiala este "alba", dar defapt este albastru
		// sa fiu sincer, eu implementasem initial platforma culoarea alba si am incercat
		// sa schimb in albastru, si nu am reusit de nicio culoare sa mearga, asa ca am lasat asa :))
		plank[i].initColor = "white";

		// random reprezinta o valoare aleatoare pentru generarea celor trei coloane
		random = rand() % 3;

		// random2 reprezinta o probabilitate (1/6) sa pice o platforma verde/galbena/orange
		random2 = rand() % 6;

		// random3 reprezinta o probabilitate (1/7) sa pice o platforma rosie
		random3 = rand() % 7;

		if (random2 == 5) {
			plank[i].color = "green";
			plank[i].initColor = "green";
		}
		if (random2 == 1) {
			plank[i].color = "orange";
			plank[i].initColor = "orange";
		}
		if (random3 == 1) {
			plank2[i].color = "red";
			plank2[i].initColor = "red";
		}
		if (random2 == 0) {
			plank2[i].color = "yellow";
			plank2[i].initColor = "yellow";
		}

		// daca i-ul este 0, adica prima linie de platforme, vreau ca neaparat platforma sa fie centrata
		// de aceea exclud random-ul din aceasta parte
		if (i == 0) {
			plank[i].color = "white";
			plank2[i].color = "white";
			plank[i].poz.x = -2;
			plank2[i].poz.x = -9.f;
			invizPlank[i].poz.x = 5.f;
			continue;
		}

		/* 
			in functie de cum pica random, generez platformele
			plank / plank2 / invizPlank reprezinta cele 3 coloane
			invizPlank nu o sa fie render-uit, de aici si faptul ca sunt invizibile
		*/ 
		
		if (random == 0) {
			plank[i].poz.x = -2;
			plank2[i].poz.x = -9.f;
			invizPlank[i].poz.x = 5.f;
		}
		else if (random == 1) {
			plank[i].poz.x = -9.f;
			plank2[i].poz.x = 5.f;
			invizPlank[i].poz.x = -2;
		}
		else {
			plank[i].poz.x = 5.f;
			plank2[i].poz.x = -2;
			invizPlank[i].poz.x = -9.f;
		}
	}

	// setarea pozitiei platformelor
	for (int i = 0; i < nrPlanks; i++) {
		plank[i].poz = glm::vec3(plank[i].poz.x, 0, -15 * i);
		plank[i].pozFin = plank[i].poz + glm::vec3(0, 0, -15);
		plank2[i].poz = glm::vec3(plank2[i].poz.x, 0, -15 * i);
		plank2[i].pozFin = plank2[i].poz + glm::vec3(0, 0, -15);
		invizPlank[i].poz = glm::vec3(invizPlank[i].poz.x, 0, -15 * i);
		invizPlank[i].pozFin = invizPlank[i].poz + glm::vec3(0, 0, -15);
	}
}

void PlankFunc::planksOutOfVision(int &nrPlanks, MyCamera* camera, Plank* plank, Plank* plank2, Plank* invizPlank) {
	/* 
	* demersul principal al acestei functii este acesta:
	* daca a fost o alta culoare decat albastra, ii redau culoarea
	* daca a avut powerup setat, il resetez
	* cand z-ul camerei depaseste z-ul final al platformei, inseamna ca pot sa nu o mai renderuiesc
	*/
	for (int i = 0; i < nrPlanks; i++) {
		// verificare cand iese din campul vizual platforma
		// sa nu o mai randez
		if (camera->getPosition().z <= plank[i].pozFin.z) {
			if (plank[i].color != "green" && plank[i].color != "orange") {
				plank[i].color = "white";
			}
			if (plank[i].color == "white" && plank[i].initColor == "green") {
				plank[i].color = "green";
			}
			if (plank[i].color == "white" && plank[i].initColor == "orange") {
				plank[i].color = "orange";
			}

			// setez fals cand iese din campul vizual toate aceste valori
			// ca powerup-ul sa nu mai fie existent
			plank[i].giveGas = false;
			plank[i].gaveGas = false;
			plank[i].giveSpeed = false;
			plank[i].gaveSpeed = false;
			plank[i].counter++;
			plank[i].poz.z = ((-15 * i) - 15 * nrPlanks * plank[i].counter);
			// reinitializez pozitia platformei

			plank[i].pozFin.z = plank[i].poz.z - 15;
		}
		if (camera->getPosition().z <= plank2[i].pozFin.z) {
			if (plank2[i].color != "red") {
				plank2[i].color = "white";
			}
			if (plank2[i].color == "white" && plank2[i].initColor == "red") {
				plank2[i].color = "red";
			}
			if (plank2[i].color == "white" && plank2[i].initColor == "yellow") {
				plank2[i].color = "yellow";
			}
			plank2[i].loseGas = false;
			plank2[i].lostGas = false;
			plank2[i].counter++;
			plank2[i].poz.z = ((-15 * i) - 15 * nrPlanks * plank2[i].counter); // - 15 -> -105 -> ...
			// reinitializez pozitia platformei

			plank2[i].pozFin.z = plank2[i].poz.z - 15;
		}
		if (camera->getPosition().z <= invizPlank[i].pozFin.z) {
			// aceste platforme nu vor fi randate, si sunt folosite pentru a-mi da seama daca
			// sfera a iesit in afara hartii
			invizPlank[i].counter++;
			invizPlank[i].poz.z = ((-15 * i) - 15 * nrPlanks * invizPlank[i].counter); // - 15 -> -105 -> ...
			invizPlank[i].pozFin.z = invizPlank[i].poz.z - 15;
		}
	}
}

void PlankFunc::powerupsPlank(Plank* plank2, Plank* plank, Gas &gas, bool &speedy, int& i, bool &gasMod, int& secSpeed, int& secGas) {
	if (plank2[i].endGame) {
		// platforma rosie

		cout << "Ai atins o platforma rosie, ai murit!" << endl;
		plank2[i].endGame = false;
		exit(-1);
	}
	if (plank2[i].loseGas) {
		// platforma galbena

		cout << "Ai pierdut combustibil!" << endl;
		plank2[i].loseGas = false;
		gasMod = true;
		secGas = 1;
		gas.fuel -= 5.0f;
	}
	if (plank[i].giveGas) {
		// platforma verde

		cout << "Ai primit combustibil inapoi!" << endl;
		plank[i].giveGas = false;
		gasMod = true;
		secGas = 1;
		if (gas.fuel >= 15.f) {
			gas.fuel = 30.f;
		}
		else {
			gas.fuel += 15.f;
		}
	}
	if (plank[i].giveSpeed) {
		// platforma orange

		speedy = true;
		secSpeed = 1;
		if (!speedy) {
			plank[i].giveSpeed = false;
		}
	}
}