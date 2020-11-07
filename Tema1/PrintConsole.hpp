#pragma once
#include <iostream>

using namespace std;

void addScoreBalloons(string balloonColor[3], int &score, int i) {
	if (balloonColor[i] == "red") {
		score += 100;
	}
	else if (balloonColor[i] == "yellow") {
		score -= 50;
	}
}

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