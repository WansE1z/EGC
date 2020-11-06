#pragma once
#include <iostream>

using namespace std;


void PrintFinish(int& lifes, int& score) {
	if (lifes == 0) {
		cout << "-------------------------------------- END OF GAME --------------------------------------" << endl;
		cout << "You have lost all of your lifes" << endl;
		cout << endl;
		cout << "--------------------------------------    SCORE    --------------------------------------" << endl;
		cout << "The game was finished with the score: " << score;
		cout << endl;
		exit(0);
	}
}

void PrintScore(int& seconds, int& score) {
	seconds++;
	if (seconds % 500 == 0) {
		cout << "The score right now is : " << score << endl;
	}
}