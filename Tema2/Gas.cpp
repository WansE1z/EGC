#include "Gas.h"

void GasFunc::outOfFuel(Gas& gas) {
	gas.fuel -= 0.01f;
	if (gas.fuel <= 0) {
		cout << "You have lost the game! You have no gas left!" << endl;
		exit(-1);
	}
}