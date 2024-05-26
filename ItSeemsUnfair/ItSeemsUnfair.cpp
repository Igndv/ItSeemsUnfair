// ItSeemsUnfair.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include <time.h>
#include <conio.h>

using namespace std;

//assign class
class core {
protected:
	string name;
	int level,HP, attack,heal,playerIndex,enemyIndex;
	int damageConflict, healConflict;

public: // jan lupa bikin modul buat modify main core : level,HP,attack

	core() { 
	}
	//player stats
	void mainPlayerStats() { //stats awal player 1
		name = "Ralph";
		level = 60;
		HP = 40;
		attack = 15;
		heal = 0;
		playerIndex = 1;
	}

	void magePlayerStats() { //stats awal player 2
		name = "Aurora";
		level = 55;
		HP = 30;
		attack = 25;
		heal = 15;
		playerIndex = 2;
	}
	//player stats end


	//enemy stats : semua stats monster yang berbeda2
	void enemySkeleton() {
		name = "Skeleton";
		level = 5;
		HP = 15;
		attack = 5;
		heal = 0;
		enemyIndex = 0;
	}

	void enemyZombie() {
		name = "Zombie";
		level = 7;
		HP = 25;
		attack = 7;
		heal = 0;
		enemyIndex = 0;
	}

	//enemy stats end

	//Set enemy 1,2,3,4
	void enemy1() {

	}

	void enemy2() {

	}

	void enemy3() {

	}

	void enemy4() {

	}

	//Player Juggle Stats
	void playerStatsJuggle() {
		if (playerIndex == 1) {
			this->mainPlayerStats();
		}
		else if (playerIndex == 2) {
			this->magePlayerStats();
		}
	}

	//Enemy Juggle Stats (max enemy 4)
	void enemyStatsJuggle() {

		if (enemyIndex == 1) {
			this->enemy1();
		}
		else if (enemyIndex == 2) {
			this->enemy2();
		}
		else if (enemyIndex == 3) {
			this->enemy3();
		}
		else if (enemyIndex == 4) {
			this->enemy4();
		}

	}

	//Get Interaction
	void getDamage() {
		damageConflict = attack;
	}

	void getHeal() {
		healConflict = heal;
	}

	void checkStats() { //cek statistik
		cout << name << "'s Level = " << level << endl << "HP = " << HP << endl << "Attack = " << attack << endl << playerIndex << endl;
	}
};

class playerStats : public core {
public:

	playerStats() { //default constuctor
	}
};

class enemyStats : public core { //create statistik musuh
public:

	enemyStats() { //constructor with (HP,attack,enemyIndex)
	}
};

class Battle : public core { //dicebattle dll nti masuk sini semua
private:
	bool roundWinner;
	int playerHP, playerAttack, enemyHP, enemyAttack;

public:

	void singleAttack() {
		this->getDamage();
		HP = HP - damageConflict;
		cout << "Single Attack was Initialized!" << endl; //harusnya aman si
	}

	void wideAttack() {
		cout << "Wide Attack was Initialized!" << endl; //belum atur
	}


	void block() {
		cout << "Block was Initialized!" << endl; //belum atur

	}

	void heal() {
		this->getHeal();
		HP = HP + healConflict;
		cout << "Heal was Initialized!" << endl; 

	}

	void interactionMenu() { //Menu interaksi, sementara pake cout (belum dibedain buat player 1 dan 2)
		char ch;

		cout << name << "Player wants to :" << endl << "1. Single Attack" << endl << "2.Wide Attack" << endl << "3.Block" << endl<<"4.Heal" << endl;

		ch = _getch();
		if (ch == '1') {
			this->singleAttack();
		}
		else if (ch == '2') {
			this->wideAttack();
		}
		else if (ch == '3') {
			this->block();
		}
		else if (ch == '4') {
			this->heal();
		}
		else {
			this->interactionMenu();
		}

	}

	void interaciton() { //Fungsi buat ngluarin interaksi
		char ch;

		if (roundWinner == 1) {
			this->interactionMenu();
		}
	}

	void diceBattle() { //+interaction when win dice
		int dice1, dice2;
		char ch;
		srand(time(0));

		cout << "Press space to roll dice!" << endl;
		ch = _getch();
		if (ch == ' ') {
			dice1 = (rand() % 6) + 1;
			dice2 = (rand() % 6) + 1;

			if (dice1 > dice2) {
				cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Your Chance to attack!" << endl;
				roundWinner = 1;
				cout << roundWinner << endl;
				this->interaciton();
				cout << "------------------------------------------" << endl;
				cout << endl;
			}
			else if (dice1 < dice2) {
				cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Enemy's Chance to attack!" << endl;
				roundWinner = 0;
				cout << roundWinner << endl;
				cout << "------------------------------------------" << endl;
				cout << endl;

			}
			else if (dice1 == dice2) {
				cout << "TIE" << endl;
				cout << "------------------------------------------" << endl;
				cout << endl;
			}
		}
		else {
		}

	}


	void battle(int _enemyCount) {
		int playerCount, enemyCount;
		bool playerIsAlive = 1, enemyIsAlive = 1; //checks if there is still player or enemies are still alive


		playerCount = 2;//player and enemy count masih misal untuk test aja
		enemyCount = _enemyCount;


		while (playerIsAlive == 1 || enemyIsAlive == 1) {	//selama check player / enemy belum mati jalan tros.. +dice battle interaction belum
			for (playerIndex = 1; playerIndex <= playerCount; playerIndex++)
				for (enemyIndex = 1; enemyIndex <= enemyCount; enemyIndex++) {
					this->playerStatsJuggle();
					this->enemyStatsJuggle();
					cout << "Player Index = " << playerIndex << " is attacking " << enemyIndex << endl;
					cout << "Test Player = ";
					checkStats();
					cout << endl;
					this->diceBattle();
				}

		}
	}
};

class animation { //draw model taru sini semua

};

int main()
{

	//Set main player and mage stats
	playerStats KnightPlayer;
	KnightPlayer.mainPlayerStats();
	KnightPlayer.checkStats(); cout << endl;

	playerStats MagePlayer;
	MagePlayer.magePlayerStats();
	MagePlayer.checkStats(); cout << endl;

	//Enemy Stats trial
	enemyStats enemy1();
	enemyStats ememy2();


	cout << "Hello World" << endl << endl;

	Battle StartBattle;
	StartBattle.battle(3); //insert jumlah musuh
		return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
