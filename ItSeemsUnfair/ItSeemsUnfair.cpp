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
	int level, HP, attack, heal;
	int newHP;

public: // jan lupa bikin modul buat modify main core : level,HP,attack

	core() {
	}

	//Get info
	int getDamage() const{
		return attack;
	}

	int getHeal() const{
		return heal;
	}

	int getHP() const{
		return HP;
	}

	string getName() const {
		return name;
	}

	void setHp(int newHp) {
		HP = newHp;
	}

	void checkStats() { //cek statistik
		cout << name << "'s Level = " << level << endl << "HP = " << HP << endl << "Attack = " << attack << endl;
	}
};

class playerStats : public core {
public:

	playerStats(string _nama, int _level, int _HP, int _attack, int _heal) { // built constuctor with Level, HP, Atack, Heal, playerIndex
		name = _nama;
		level = _level;
		HP = _HP;
		attack = _attack;
		heal = _heal;
	}
};

class enemyStats : public core { //create statistik musuh
public:

	enemyStats(string _name, int _level, int _HP, int _attack, int _heal) { //built constructor with Level, HP, Attack, Heal, enemyIndex
		name = _name;
		level = _level;
		HP = _HP;
		attack = _attack;
		heal = _heal;
	}
};

class Battle : public core { //dicebattle dll nti masuk sini semua
private:
	bool roundWinner;
	string rarity;

public:

	//slash
	void slash_Player(playerStats& player,enemyStats& enemy) { //slash from enemy to player <-> player to enemy
		int damage;
		damage = player.getDamage();
		cout << damage;
		this->getSlash_Enemy(enemy, damage);
	}

	void slash_Enemy(playerStats& player,enemyStats& enemy) {
		int damage;
		damage = enemy.getDamage();
		cout << damage;
		this->getSlash_Player(player, damage);
	}

	void getSlash_Player(playerStats& player,int slash) { //update health from damage recieved from enemy - parameter damage from enemy
		int health = player.getHP();
		health = health - slash;
		this->setHp(health);
	}

	void getSlash_Enemy(enemyStats& enemy, int slash) { //update health from damage recieved from enemy - parameter damage from enemy
		int health = enemy.getHP();
		health = health - slash;
		this->setHp(health);
	}

	void slashAttack(playerStats& player, enemyStats& enemy) {
		this->slash_Player(player,enemy);
		cout << "Slash was Initialized! (" << attack << ")" << endl;
	}
	//slash end

	// heal

	void getHeal_Player(playerStats& player, enemyStats& enemy) {
		int healing;
	}

	void heal() {
		this->getHeal();
		cout << "Heal was Initialized!" << endl;

	}

	//heal end

	//item
	void itemPick() {
		this->getDamage();
		cout << "Wide Attack was Initialized! (" << attack << ")" << endl;
	}

	//item end

	void interactionMenu(playerStats& player,enemyStats& enemy) { //Menu interaksi, sementara pake cout (belum dibedain buat player 1 dan 2)
		char ch;
		cout << name << "Player wants to :" << endl << "1. Single Attack" << endl << "2. Wide Attack" << endl << "3. Block" << endl << "4. Heal" << endl;

		ch = _getch();
		if (ch == '1') {
			this->slash_Player(player,enemy);
		}
		else if (ch == '2') {
			this->heal();
		}
		else if (ch == '3') {
			this->itemPick();
		}
		else {
			this->interactionMenu(player,enemy);
		}

	}

	void enemyLogic(playerStats& player, enemyStats& enemy) { //enemy baru cuman bisa attack
		cout << enemy.getName() << " wants to Attack (-" << enemy.getDamage() << ")" << endl;
		slash_Enemy(player,enemy);

	}


	void diceBattle(playerStats& player, enemyStats& enemy) { //+interaction when win dice
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
				cout << roundWinner << endl;
				interactionMenu(player,enemy);
				cout << "------------------------------------------" << endl;
				cout << endl;
			}
			else if (dice1 < dice2) {
				cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Enemy's Chance to attack!" << endl;
				cout << roundWinner << endl;
				enemyLogic(player,enemy);
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

	//items : player is ABLE to use 1 item before his move ->optional
	void item_shield() { //add nx(?) shield that can tank damage, so the player doesnt get damage at ALL.
		rarity = "Epic";
	}

	void item_poisonSword() { // Effect used in player's next attack and deals poison which can (1. -HP for enemy every turn for n(?) turn ; 2.Debuff lower damage(?))
		rarity = "Rare";
	}

	void item_angelRay() { //like flashbang, stuns enemy in the next turn (guarantee turn on next one -> skip roll dice -> interaction menu)
		rarity = "Rare";
	}

	void item_realityAlter() { //"bend reality to your will" incrase your max dice.
		rarity = "Epic";
	}

	void item_immortal() { // grant revive with half health.
		rarity = "Legendary";
	}

	//item effect logic
	void itemLogic() {

	}

	void battle(playerStats& player, enemyStats& enemy) {	// battle begins lol
		while (player.getHP() != 0 || enemy.getHP() != 0) {
			this->diceBattle(player, enemy);
			player.checkStats();
			enemy.checkStats();
		}
	}


	//levels : tutorial
	void tutorial() {
		playerStats player("Ralph", 60, 40, 15, 0);
		enemyStats slime("Tutorial Slime", 1, 2, 2, 1);
	}

	//transisi dr tutorial ke level 1 - 2

	void level1_stage1() {
		playerStats player("Ralph", 60, 40, 20, 10);

	}

	void level1_stage2() {
		playerStats player("Ralph", 60, 40, 20, 10);
	}

	void level1_stage3() {
		playerStats player("Ralph", 60, 40, 20, 10);
	}

	//transisi level 1 - 2

	void level2_stage1() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	void level2_stage2() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	void level2_bossStage() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	//tansisi level 2 - 3 (jan lup stats player turun)

	void level3_stage1() {
		playerStats player("Ralph", 45, 30, 16, 7);
	}

	void level3_stage2() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	void level3_stage3() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	void level3_gateKeeper() {
		playerStats player("Ralph", 45, 30, 15, 7);
	}

	//masuk ke kastil iblis transisi ke 3 - 4

	void level4_stage1() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	void level4_stage2() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	void level4_stage3() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	//masuk ke dragon realm transisi ke 4 - 5

	void level5_stage1() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	void level5_stage2() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	void level5_stage3() {
		playerStats player("Ralph", 25, 20, 10, 5);
	}

	//final boss

	void finalBoss() {
		playerStats player("Ralph", 12, 10, 5, 2);
	}
};

class animation { //draw model taru sini semua

};

int main()
{
	
	//Set main player and mage stats
	playerStats Player("Ralph", 60, 40, 15, 0);
	Player.checkStats(); cout << endl;

	//Enemy Stats trial
	enemyStats Skeleton("Skeleton", 5, 15, 5, 0);
	Skeleton.checkStats(); cout << endl;
	



	cout << "-------------------------------" << endl << endl;

	Battle StartBattle;
	StartBattle.battle(Player,Skeleton); //insert jumlah musuh
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu