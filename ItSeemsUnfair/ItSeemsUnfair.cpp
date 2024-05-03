// ItSeemsUnfair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
using namespace std;

class Character {
protected:
	int health;
	int damage;
public:
	bool turn;
	int count[];

	Character() {
	}

	void displayInfo() {
		//display health + turn
	}

	void turnLogic() {
		//turn logic where the player and enemy takes turn on rolling the dice
	}
};

class Player : Character {
private:
	int playerCount = 4;
public:
	Player(int getHealth, int getDamage, bool getTurn, int getCount) {
		health = getHealth;
		damage = getDamage;
		turn = getTurn;
		count[playerCount] = getCount;
	}

	int playerStats(int getHealth, int getDamage, int getTurn) {
		// gatau mau void ato int nanti bs print health player, damage, turn
	}

	void playerTurn() {
		// players turn gatau pake ga ya?
	}



};






int main()
{
   cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
