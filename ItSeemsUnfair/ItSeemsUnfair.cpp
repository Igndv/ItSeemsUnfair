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
	int level, HP, attack, heal, playerIndex, enemyIndex;
	int damageConflict, healConflict;
	int newHP;

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
		name = "Skeleton1";
		level = 5;
		HP = 15;
		attack = 5;
		heal = 0;
		enemyIndex = 0;
	}

	void enemyZombie() {
		name = "Zombie3";
		level = 7;
		HP = 25;
		attack = 7;
		heal = 0;
		enemyIndex = 0;
	}

	void enemySlime() {
		name = "Slime2";
		level = 3;
		HP = 5;
		attack = 5;
		heal = 0;
		enemyIndex = 0;
	}

	void enemyDragon() {
		name = "Dragon4";
		level = 15;
		HP = 35;
		attack = 15;
		heal = 0;
		enemyIndex = 0;
	}
	//enemy stats end


	//Set Player 1,2
	void player1() {
		mainPlayerStats();
	}

	void player2() {
		magePlayerStats();
	}
	//Set Player 1,2 end 


	//Set enemy 1,2,3,4
	void enemy1() {
		enemySkeleton();
		enemyIndex = 1;
	}

	void enemy2() {
		enemySlime();
		enemyIndex = 2;
	}

	void enemy3() {
		enemyZombie();
		enemyIndex = 3;
	}

	void enemy4() {
		enemyDragon();
		enemyIndex = 4;
	}

	//Player Juggle Stats
	void playerStatsJuggle() {
		if (playerIndex == 1) {
			player1();
		}
		else if (playerIndex == 2) {
			player2();
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

	void setHp(int newHp) {
		HP = newHp;
	}

	void checkPlayerStats() { //cek statistik
		cout << name << "'s Level = " << level << endl << "HP = " << HP << endl << "Attack = " << attack << endl << playerIndex << endl;
	}

	void checkEnemyStats() { //cek statistik
		cout << name << "'s Level = " << level << endl << "HP = " << HP << endl << "Attack = " << attack << endl << enemyIndex << endl;
	}
};

class playerStats : public core {
public:

	playerStats(string _nama, int _level, int _HP, int _attack, int _heal, int _playerIndex) { // built constuctor with Level, HP, Atack, Heal, playerIndex
		name = _nama;
		level = _level;
		HP = _HP;
		attack = _attack;
		heal = _heal;
		playerIndex = _playerIndex;
	}


};

class enemyStats : public core { //create statistik musuh
public:

	enemyStats(string _name, int _level, int _HP, int _attack, int _heal, int _enemyIndex) { //built constructor with Level, HP, Attack, Heal, enemyIndex
		name = _name;
		level = _level;
		HP = _HP;
		attack = _attack;
		heal = _heal;
		enemyIndex = _enemyIndex;
	}


};

class Battle : public core { //dicebattle dll nti masuk sini semua
private:
	bool roundWinner;
	int playerHP, playerAttack, enemyHP, enemyAttack;

public:

	void singleAttack() {
		this->getDamage();
		newHP = HP - damageConflict;
		cout << "Single Attack was Initialized! (" << attack << ")" << endl; //harusnya aman si
	}

	void wideAttack() {
		this->getDamage();
		HP = HP - (damageConflict / 3);
		cout << "Wide Attack was Initialized! (" << attack << ")" << endl; //belum atur
	}


	void block() {
		cout << "Block was Initialized!" << endl; //belum atur

	}

	void heal() {
		this->getHeal();
		newHP = HP + healConflict;
		cout << "Heal was Initialized!" << endl;

	}

	void interactionMenu() { //Menu interaksi, sementara pake cout (belum dibedain buat player 1 dan 2)
		char ch;
		this->playerStatsJuggle();
		cout << name << "Player wants to :" << endl << "1. Single Attack" << endl << "2. Wide Attack" << endl << "3. Block" << endl << "4. Heal" << endl;

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

	void enemyLogic() { //enemy baru cuman bisa attack
		this->enemyStatsJuggle();
		cout << name << " wants to Attack (-" << attack << ")" << endl;
		this->singleAttack();

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
				this->enemyLogic();
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
					//player
					cout << "Player Index = " << playerIndex << " is attacking " << enemyIndex << endl;
					this->playerStatsJuggle();
					cout << "Test Player = ";
					checkPlayerStats();
					cout << endl;
					//enemy
					this->enemyStatsJuggle();
					cout << "Test Enemy = ";
					checkEnemyStats();
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
	playerStats MainPlayer("Ralph", 60, 40, 15, 0, 1);
	MainPlayer.checkPlayerStats(); cout << endl;

	playerStats MagePlayer("Aurora", 55, 30, 25, 15, 2);
	MagePlayer.checkPlayerStats(); cout << endl;

	//Enemy Stats trial
	enemyStats Skeleton("Skeleton 1", 5, 15, 5, 0, 0);
	Skeleton.checkEnemyStats(); cout << endl;
	enemyStats Slime("Slime 2", 3, 5, 5, 0, 0);
	Slime.checkEnemyStats(); cout << endl;
	enemyStats Zombie("Zombie 3", 7, 25, 7, 0, 0);
	Zombie.checkEnemyStats(); cout << endl;
	enemyStats Dragon("Dragon 4", 15, 35, 15, 0, 0);
	Dragon.checkEnemyStats(); cout << endl;



	cout << "-------------------------------" << endl << endl;

	//Battle StartBattle;
	//StartBattle.battle(4); //insert jumlah musuh
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu