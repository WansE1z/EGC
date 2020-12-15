#include "Gas.h"

void GasFunc::outOfFuel(Gas& gas) {
	// scad din combustibil o valoarea constanta
	gas.fuel -= 0.01f;
	if (gas.fuel <= 0) {
		cout << "Nu mai ai combustibil!" << endl;
		cout << "--------------------------------  END OF GAME  --------------------------------" << endl;
		exit(-1);
	}
}