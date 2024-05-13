// ItSeemsUnfair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"

using namespace std;

void diceBattle() { //battle dice tapi belum dgn kbhit space, +interaction when win dice
	int dice1, dice2;
	bool roundWinner;

	cout << "Press space to roll dice!" << endl;
	dice1 = rand() % 7;
	dice2 = rand() % 7;

	if (dice1 > dice2) {
		cout << "Your Chance to attack!" << endl;
		roundWinner = 1;

	}
	else if (dice1 < dice2) {
		cout << "Enemy's Chance to attack!" << endl;
		roundWinner = 0;

	}
	else if (dice1 == dice2) {
		diceBattle();
	}
}

void battle() {
	int playerCount, enemyCount, playerIndex, enemyIndex;
	bool turn_check = 0, player_check = 0, enemy_check = 0;

	playerCount = 1;//player and enemy count masih misal untuk test aja
	enemyCount = 2;

	while (player_check != 0 || enemy_check != 0) {	//selama check player / enemy belum mati jalan tros.. +dice battle interaction belum
		for (playerIndex = 1; playerIndex <= playerCount; playerIndex++) {

			for (enemyIndex = 1; enemyIndex <= enemyCount; enemyIndex++) {
				diceBattle();
			}

		}
	}
}

int main()
{ 
	cout << "Hello World";
		return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
