// ItSeemsUnfair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include <time.h>
#include <conio.h>

using namespace std;

//assign class
class stats {
protected:
	int level,HP, attack;

public: // jan lupa bikin modul buat modify main stats : level,HP,attack

	stats() { //constructor
		level = 0;
		HP = 0;
		attack = 0;
	}
};

class playerStats : stats {
public:
	int playerIndex;

	playerStats() { //constuctor
		level = 0;
		HP = 0;
		attack = 0;
		playerIndex = 0;
	}

	void mainPlayerStats() {
		level = 60;
		HP = 40;
		attack = 15;
		playerIndex = 1;
	}

	void magePlayerStats() {
		level = 55;
		HP = 30;
		attack = 25;
		playerIndex = 2;
	}
};

class enemyStats : stats {
	int enemyIndex;

	enemyStats(int _HP, int _attack, int _enemyIndex) {
		HP = _HP;
		attack = _attack;
		enemyIndex = _enemyIndex;
	}

};

class Battle { //dicebattle dll nti masuk sini semua

};

class interaction : Battle{ //battle child

};

class animation { //draw model taru sini semua

};


//func sementara

void diceBattle() { //battle dice tapi belum dgn kbhit space, +interaction when win dice
	int dice1, dice2;
	bool roundWinner;
	char ch;
	srand(time(0));

	cout << "Press space to roll dice!" << endl;
	ch = _getch();
	if (ch==' ') {
		dice1 = (rand() % 6) + 1;
		dice2 = (rand() % 6) + 1;

		if (dice1 > dice2) {
			cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Your Chance to attack!" << endl;
			roundWinner = 1;

		}
		else if (dice1 < dice2) {
			cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Enemy's Chance to attack!" << endl;
			roundWinner = 0;

		}
		else if (dice1 == dice2) {
			cout << "TIE" << endl;
			diceBattle();
		}
	}
	else {
		diceBattle();
	}
}

void interaction() { //inside battle class
	int attack, heal;

}

void battle() {
	int playerCount, enemyCount, playerIndex, enemyIndex;
	bool playerIsAlive = 1, enemyIsAlive = 1; //checks if there is still player or enemies are still alive

	playerCount = 1;//player and enemy count masih misal untuk test aja
	enemyCount = 2;

	while (playerIsAlive == 1 || enemyIsAlive == 1) {	//selama check player / enemy belum mati jalan tros.. +dice battle interaction belum
		for (playerIndex = 1; playerIndex <= playerCount; playerIndex++) {

			for (enemyIndex = 1; enemyIndex <= enemyCount; enemyIndex++) {
				diceBattle();
			}

		}
	}
}

int main()
{ 
	cout << "Hello World"<<endl;
	battle();
		return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
