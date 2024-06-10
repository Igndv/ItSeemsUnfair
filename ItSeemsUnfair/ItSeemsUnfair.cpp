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
    int shield_count = 0, poison_count = 0, angleRay_count = 0, realityAlter_count = 0, immortal_count = 0, raygun_count = 0; //items count

public:
    core() {
    }

    //Get info
    int getDamage() const {
        return attack;
    }

    int getHeal() const {
        return heal;
    }

    int getHP() const {
        return HP;
    }

    string getName() const {
        return name;
    }

    void setHP(int newHP) {
        HP = newHP;
    }

    void checkStats() { //cek statistik
        cout << name << "'s Level = " << level << endl << "HP = " << HP << endl << "Attack = " << attack << endl;
    }
};

class playerStats : public core {
public:
    playerStats(string _nama, int _level, int _HP, int _attack, int _heal) { // built constructor with Level, HP, Atack, Heal, playerIndex
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
    string rarity;

public:
    int maxHP_Player, maxHP_Enemy;

    bool itemAvail() {
        bool avail;
        if (shield_count == 0 || poison_count == 0 || angleRay_count == 0 || realityAlter_count == 0 || immortal_count == 0 || raygun_count == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }

    void getMaxHP(playerStats& player, enemyStats& enemy) { //taru diawal ya biar bisa ambil max HP nya sekali aja
        maxHP_Player = player.getHP();
        maxHP_Enemy = enemy.getHP();
    }

    //slash
    void slash_Player(playerStats& player, enemyStats& enemy) { //slash from enemy to player <-> player to enemy
        int damage = player.getDamage();
        cout << player.getName() << " attacks " << enemy.getName() << " for " << damage << " damage." << endl;
        getSlash_Enemy(enemy, damage);
    }

    void slash_Enemy(playerStats& player, enemyStats& enemy) {
        int damage = enemy.getDamage();
        cout << enemy.getName() << " attacks " << player.getName() << " for " << damage << " damage." << endl;
        getSlash_Player(player, damage);
    }

    void getSlash_Player(playerStats& player, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = player.getHP();
        health -= slash;
        player.setHP(health);
        cout << player.getName() << "'s HP is now " << player.getHP() << endl;
    }

    void getSlash_Enemy(enemyStats& enemy, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = enemy.getHP();
        health -= slash;
        enemy.setHP(health);
        cout << enemy.getName() << "'s HP is now " << enemy.getHP() << endl;
    }

    void slashAttack(playerStats& player, enemyStats& enemy) {
        slash_Player(player, enemy);
        cout << "Slash was Initialized! (" << attack << ")" << endl;
    }

    // heal
    void getHeal_Player(playerStats& player) {
        int healing = player.getHeal();
        int health = player.getHP();
        health += healing;
        if (health >= this->maxHP_Player) {
            health = this->maxHP_Player;
        }
        player.setHP(health);
        cout << player.getName() << " healed for " << healing << " HP. HP is now " << player.getHP() << endl;
    }

    void heal_Player(playerStats& player) {
        getHeal_Player(player);
        cout << "Heal was Initialized!" << endl;
    }

    // heal end

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

    void item_raygun() { //cheat item = instant kill
        rarity = "Cheat";
    }

    //item
    void itemPick() {
        char ch;

        cout << "Choose your item to use:\n" << "1. Shield " << shield_count << "\n 2. Poison Sword " << poison_count << "\n 3. Angle Ray " << angleRay_count << "\n 4. Reality Alter " << realityAlter_count << "\n 5. Immortal " << immortal_count << "\n 6. ??? " << raygun_count;

        ch = _getch();

        if (ch == '1') { //shield
            if (shield_count > 0) {
                this->item_shield();
                shield_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
        else if (ch == '2') { //poison
            if (poison_count > 0) {
                this->item_poisonSword();
                poison_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
        else if (ch == '3') { //angle ray
            if (angleRay_count > 0) {
                this->item_angelRay();
                angleRay_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
        else if (ch == '4') { //reality alter
            if (realityAlter_count > 0) {
                this->item_realityAlter();
                realityAlter_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
        else if (ch == '5') { // immortal
            if (immortal_count > 0) {
                this->item_immortal();
                immortal_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
        else if (ch == '6') { // ??? / raygun (cheat)
            if (raygun_count > 0) {
                this->item_raygun();
                raygun_count--;
            }
            else {
                cout << "Item not owned\n";
            }
        }
    }

    //item end

    void interactionMenu(playerStats& player, enemyStats& enemy) { //Menu interaksi, sementara pake cout (belum dibedain buat player 1 dan 2)
        char ch;
        bool doneItem = 0;
        cout << player.getName() << " wants to :" << endl << "1. Slash" << endl << "2. Heal" << endl << "3. Item" << itemAvail() << endl;

        ch = _getch();
        if (ch == '1') {
            slash_Player(player, enemy);
        }
        else if (ch == '2') {
            heal_Player(player);
        }
        else if (ch == '3') {
            if (itemAvail() == 1 && doneItem == 0) {
                this->itemPick(); //cuman bisa sekali && ketika punya item doang baru bisa akses
                doneItem = 1;
            }
            else {
                cout << "Items are not Available\n";
            }
            interactionMenu(player, enemy);
        }
        else {
            interactionMenu(player, enemy);
        }
    }

    void enemyLogic(playerStats& player, enemyStats& enemy) { //enemy baru cuman bisa attack
        cout << enemy.getName() << " wants to Attack (-" << enemy.getDamage() << ")" << endl;
        slash_Enemy(player, enemy);
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
                interactionMenu(player, enemy);
                cout << "------------------------------------------" << endl;
                cout << endl;
            }
            else if (dice1 < dice2) {
                cout << "Your Roll : " << dice1 << " | Your Enemy Roll : " << dice2 << endl << "Enemy's Chance to attack!" << endl;
                enemyLogic(player, enemy);
                cout << "------------------------------------------" << endl;
                cout << endl;
            }
            else if (dice1 == dice2) {
                cout << "TIE" << endl;
                cout << "------------------------------------------" << endl;
                cout << endl;
            }
        }
    }

    void battle(playerStats& player, enemyStats& enemy) { // battle begins lol
        getMaxHP(player, enemy); // get max HP
        cout << "\nMax Player HP : " << maxHP_Player << "\nMax Enemy HP : " << maxHP_Enemy << endl;

        while (player.getHP() > 0 && enemy.getHP() > 0) {
            diceBattle(player, enemy);
            player.checkStats();
            cout << "-------------\n";
            enemy.checkStats();
        }

        if (player.getHP() <= 0) {
            cout << player.getName() << " has been defeated." << endl;
        }

        if (enemy.getHP() <= 0) {
            cout << enemy.getName() << " has been defeated." << endl;
        }
    }

    //levels : tutorial
    void tutorial() {
        playerStats player("Ralph", 60, 40, 15, 10);
        player.checkStats();
        enemyStats slime("Tutorial Slime", 1, 2, 2, 1);
        slime.checkStats();

        Battle StartBattle;
        StartBattle.battle(player, slime);
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
    Battle StartTutorial;
    StartTutorial.tutorial();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu