#include <iostream>
#include <raylib.h>
#include <time.h>

using namespace std;

int screenWidth = 1280;
int screenHeight = 720;

//place holder x y lokasi enemy and player 
int uiXPlayer = 150;
int uiYPlayer = 525;

int uiXCenter =320;
int uiYcenter =360;


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

    void checkStats(int _x, int _y) { //cek statistik (lompat 30 pixel ke bawah)
        DrawText(name.c_str(), _x, _y, 30, WHITE);
        DrawText(TextFormat("HP : %d", HP), _x, _y + 40, 30, WHITE);
        DrawText(TextFormat("Attack : %d", attack), _x, _y + 80, 30, WHITE);
        DrawText(TextFormat("Heal : %d", heal), _x, _y + 120, 30, WHITE);
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

class animation {
public:
    int playerX = 250;
    int playerY = 350;
    int enemyX = 950;
    int enemyY = 200;

    //Logo
    Texture2D logo = LoadTexture("Assets/Logo/logo.PNG");
    //DrawTexture(logo, 300, 100, WHITE);  punya draw logo

    //All Background : status not init yet
    Texture2D startMenu;
    Texture2D tutorialBG;
    Texture2D level1BG;
    Texture2D level2BG;
    Texture2D level3BG;
    Texture2D level4BG;
    Texture2D level5BG;
    Texture2D finalBossBG;

    //All Effects
    Texture2D healEffect;

    //All Player Textures
    Texture2D playerLevel4;
    Texture2D playerLevel3;
    Texture2D playerLevel2;
    Texture2D playerLevel1;

    //All Enemy Textures
    Texture2D slime = LoadTexture("Assets/Enemy/slime_enemy.png");

    animation() {
        logo = LoadTexture("Assets/Logo/logo.PNG");
        //startMenu = LoadTexture("Assets/Backgrounds/start_menu.png"); // Example path
        //tutorialBG = LoadTexture("Assets/Backgrounds/tutorial_bg.png");
        //level1BG = LoadTexture("Assets/Backgrounds/level1_bg.png");
        //level2BG = LoadTexture("Assets/Backgrounds/level2_bg.png");
        //level3BG = LoadTexture("Assets/Backgrounds/level3_bg.png");
        //level4BG = LoadTexture("Assets/Backgrounds/level4_bg.png");
        //level5BG = LoadTexture("Assets/Backgrounds/level5_bg.png");
        //finalBossBG = LoadTexture("Assets/Backgrounds/final_boss_bg.png");
        //healEffect = LoadTexture("Assets/Effects/heal_effect.png");
        playerLevel4 = LoadTexture("Assets/Player/level4_player.png");
        playerLevel3 = LoadTexture("Assets/Player/level3_player.png");
        playerLevel2 = LoadTexture("Assets/Player/level2_player.png");
        playerLevel1 = LoadTexture("Assets/Player/level1_player.png");
        slime = LoadTexture("Assets/Enemy/slime_enemy.png");
    }

    void drawLoseScreen() {

    }

    void drawWinScreen() {

    }

    void drawTutorial() {
        ClearBackground(GREEN);
        DrawTexture(playerLevel4, playerX, playerY,WHITE);
        DrawTexture(slime, enemyX, enemyY, WHITE);
    }

    void drawlevel1_stage1() {
        
        DrawTexture(playerLevel4, playerX, playerY, WHITE);
        DrawTexture(slime, enemyX, enemyY, WHITE);
  
    }
};


class Battle : public core, public animation { //dicebattle dll nti masuk sini semua
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
        getSlash_Enemy(enemy, damage);

        BeginDrawing();
        DrawText(TextFormat("%s attacks %s for %d damage", player.getName().c_str(), enemy.getName().c_str(), damage), uiXCenter - 130, uiYcenter - 130, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
    }

    void slash_Enemy(playerStats& player, enemyStats& enemy) {
        int damage = enemy.getDamage();
        getSlash_Player(player, damage);

        BeginDrawing();
        DrawText(TextFormat("%s attacks %s for %d damage", enemy.getName().c_str(), player.getName().c_str(), damage), uiXCenter-130, uiYcenter-130, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
    }

    void getSlash_Player(playerStats& player, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = player.getHP();
        health -= slash;
        player.setHP(health);

        BeginDrawing();
        DrawText(TextFormat("%s's HP is now %d", player.getName().c_str(), player.getHP()), uiXCenter + 70, uiYcenter + 40, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
    }

    void getSlash_Enemy(enemyStats& enemy, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = enemy.getHP();
        health -= slash;
        enemy.setHP(health);

        BeginDrawing();
        DrawText(TextFormat("%s's HP is now %d", enemy.getName().c_str(), enemy.getHP()), uiXCenter - 130, uiYcenter - 130, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);

    }

    void slashAttack(playerStats& player, enemyStats& enemy) {
        slash_Player(player, enemy);

        BeginDrawing();
        DrawText(TextFormat("Slash was Initialiazed (%d)", attack), uiXCenter + 70, uiYcenter, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
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

        BeginDrawing();
        DrawText(TextFormat("%s is healed for %d. HP is now %d", player.getName().c_str(), healing, player.getHP()), uiXCenter + 70, uiYcenter + 40, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
    }

    void heal_Player(playerStats& player) {
        getHeal_Player(player);

        BeginDrawing();
        DrawText(TextFormat("Heal was Initialiazed (%d)", heal), uiXCenter + 70, uiYcenter, 30, WHITE);
        EndDrawing();
        WaitTime(2.0);
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
        BeginDrawing();
        DrawText("Chose Your Item to Use:", uiXPlayer, uiYPlayer, 30, WHITE);
        DrawText(TextFormat("1. Shield (%d)", shield_count), uiXPlayer, uiYPlayer + 40, 30, WHITE);
        DrawText(TextFormat("2. Poison (%d)", poison_count), uiXPlayer, uiYPlayer + 80, 30, WHITE);
        DrawText(TextFormat("3. Angle Ray (%d)", angleRay_count), uiXPlayer, uiYPlayer + 120, 30, WHITE);
        DrawText(TextFormat("4. Reality Alter (%d)", realityAlter_count), uiXPlayer, uiYPlayer + 160, 30, WHITE);
        DrawText(TextFormat("5. Immortal (%d)", shield_count), uiXPlayer, uiYPlayer + 200, 30, WHITE);
        DrawText(TextFormat("6. ??? (%d)", raygun_count), uiXPlayer, uiYPlayer + 230, 30, WHITE);
        EndDrawing();


        if (IsKeyPressed(KEY_ONE)) { //shield
            if (shield_count > 0) {
                this->item_shield();
                shield_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
        else if (IsKeyPressed(KEY_TWO)) { //poison
            if (poison_count > 0) {
                this->item_poisonSword();
                poison_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
        else if (IsKeyPressed(KEY_THREE)) { //angle ray
            if (angleRay_count > 0) {
                this->item_angelRay();
                angleRay_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
        else if (IsKeyPressed(KEY_FOUR)) { //reality alter
            if (realityAlter_count > 0) {
                this->item_realityAlter();
                realityAlter_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
        else if (IsKeyPressed(KEY_FIVE)) { // immortal
            if (immortal_count > 0) {
                this->item_immortal();
                immortal_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
        else if (IsKeyPressed(KEY_SIX)) { // ??? / raygun (cheat)
            if (raygun_count > 0) {
                this->item_raygun();
                raygun_count--;
            }
            else {
                DrawText("Item not Owned", uiXCenter, uiYcenter, 30, WHITE);
            }
        }
    }

    //item end

    void interactionMenu(playerStats& player, enemyStats& enemy) { //Menu interaksi
        bool doneItem = 0;

        BeginDrawing();
        DrawText(TextFormat("%s wants to:", player.getName().c_str()), uiXPlayer, uiYPlayer, 30, WHITE);
        DrawText("1. Slash", uiXPlayer, uiYPlayer + 40, 30, WHITE);
        DrawText("2. Heal", uiXPlayer, uiYPlayer + 80, 30, WHITE);
        DrawText(TextFormat("3. Item (%d)", itemAvail()), uiXPlayer, uiYPlayer + 120, 30, WHITE);
        EndDrawing();
        

        if (IsKeyPressed(KEY_ONE)) {
            slash_Player(player, enemy);
        }
        else if (IsKeyPressed(KEY_TWO)) {
            heal_Player(player);
        }
        else if (IsKeyPressed(KEY_THREE)) {
            if (itemAvail() == 1 && doneItem == 0) {
                this->itemPick(); //cuman bisa sekali && ketika punya item doang baru bisa akses
                doneItem = 1;
            }
            else {
                DrawText("Items are not Available", uiXCenter, uiYcenter, 30, WHITE);
            }
            interactionMenu(player, enemy);
        }
        else {
            interactionMenu(player, enemy);
        }
    }

    void enemyLogic(playerStats& player, enemyStats& enemy) {
        slash_Enemy(player, enemy);

        BeginDrawing();
        DrawText(TextFormat("%s wants to Attack (-%d)", enemy.getName().c_str(), enemy.getDamage()), uiXCenter - 130, uiYcenter - 130, 30, WHITE);
        WaitTime(2.0);
        EndDrawing();
    }

    void diceBattle(playerStats& player, enemyStats& enemy) { //+interaction when win dice

        int dice1, dice2;
        bool isSpacePressed = 0;
        srand(time(0));

        if (IsKeyPressed(KEY_SPACE)) {
            isSpacePressed = 1;
        }

        if (isSpacePressed == 0) {
            drawTutorial(); //diganti sama void drawLevel (ada level selectornya)
            BeginDrawing();
            DrawText("Press space to roll dice!", uiXCenter + 150, uiYcenter, 30, WHITE);
            EndDrawing();
        }
        else {
            dice1 = (rand() % 6) + 1;//visual untuk dice1
            dice2 = (rand() % 6) + 1;//visual untuk dice2

            DrawText(TextFormat("Your Roll : %d | Your Enemy Roll : %d", dice1, dice2), uiXCenter + 70, uiYcenter + 80, 30, WHITE);

            if (dice1 > dice2) {


                DrawText("Your Chance to Attack!", uiXCenter + 70, uiYcenter + 130, 30, WHITE);

                interactionMenu(player, enemy);
            }
            else if (dice1 < dice2) {


                DrawText("Enemy's Chance to Attack!", uiXCenter + 70, uiYcenter + 130, 30, WHITE);

                enemyLogic(player, enemy);
            }
            else if (dice1 == dice2) {
                DrawText("Tie!", uiXCenter, uiYcenter + 120, 30, WHITE);
                WaitTime(2.0);
            }
        }

        /*if (IsKeyPressed(KEY_SPACE)) {

            isSpacePressed = 1;
            dice1 = (rand() % 6) + 1;//visual untuk dice1
            dice2 = (rand() % 6) + 1;//visual untuk dice2

            DrawText(TextFormat("Your Roll : %d | Your Enemy Roll : %d", dice1, dice2), uiXCenter + 70, uiYcenter + 80, 30, WHITE);

            if (dice1 > dice2) {

                
                DrawText("Your Chance to Attack!", uiXCenter + 70, uiYcenter + 130, 30, WHITE);

                interactionMenu(player, enemy);
            }
            else if (dice1 < dice2) {

              
                DrawText("Enemy's Chance to Attack!", uiXCenter + 70, uiYcenter + 130, 30, WHITE);

                enemyLogic(player, enemy);
            }
            else if (dice1 == dice2) {
                DrawText("Tie!", uiXCenter, uiYcenter + 120, 30, WHITE);
                WaitTime(2.0);
            }
        }*/

    }

    void battle(playerStats& player, enemyStats& enemy) { // battle begins lol
 
        getMaxHP(player, enemy); // get max HP

        while (player.getHP() > 0 && enemy.getHP() > 0) {
            diceBattle(player, enemy);
            player.checkStats(0, 0);
            enemy.checkStats(800, 0);
        }

        if (player.getHP() <= 0) {

            drawTutorial();
            BeginDrawing();
            

            DrawText(TextFormat("%s has been defeated.", player.getName().c_str()), screenWidth / 2 - MeasureText(TextFormat("%s has been defeated.", player.getName().c_str()), 60) / 2, screenHeight / 2 - 50, 60, RED);
            EndDrawing();

            WaitTime(5.0);
        }

        if (enemy.getHP() <= 0) {

            drawTutorial();
            BeginDrawing();
            

            DrawText(TextFormat("%s has been defeated.", enemy.getName().c_str()), screenWidth / 2 - MeasureText(TextFormat("%s has been defeated.", enemy.getName().c_str()), 60) / 2, screenHeight / 2 - 50, 60, RED);
            EndDrawing();

            WaitTime(5.0);
        }
    }

    //levels : tutorial
    void tutorial() {

        playerStats player("Ralph", 60, 40, 15, 10);
        enemyStats slime("Tutorial Slime", 1, 5, 2, 1);
        
        BeginDrawing();
        drawTutorial();
        battle(player, slime);
        EndDrawing();
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

    void quitGame() {
        // Code to quit game
        WindowShouldClose();  // This will close the window and exit the application
    }
};

void createText(const char* text, int textX, int textY, int fontSize, Color color, float mouseX, float mouseY, Battle* battle, void (Battle::* onClick)()) {
    // Update
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;  // In Raylib, font size can be used as height

    bool isMouseOverText = (mouseX >= textX) && (mouseX <= (textX + textWidth)) &&
        (mouseY >= textY) && (mouseY <= (textY + textHeight));

    // Draw
    if (isMouseOverText) {
        DrawText(text, textX, textY, fontSize, GRAY);  // Change text color when hovered
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            (battle->*onClick)();  // Call member function using object pointer
        }
    }
    else {
        DrawText(text, textX, textY, fontSize, color);
    }
}

void game() {
    Battle startBattle;
    animation startanimation;
    Vector2 mousePosition = GetMousePosition();
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;

    BeginDrawing();
    ClearBackground(BLUE);
    DrawTexture(startanimation.logo,300,50,WHITE);
    DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 60) / 2 -325, screenHeight / 2 + 40, 60, WHITE);
    createText("o> Start Game", screenWidth / 2 - MeasureText("o> Start Game", 30) / 2 - 370, screenHeight / 2 + 120, 30, WHITE, mouseX, mouseY, &startBattle, &Battle::tutorial);
    createText("o> Quit", screenWidth / 2 - MeasureText("o> Quit", 30) / 2 - 427, screenHeight / 2 + 160, 30, WHITE, mouseX, mouseY, &startBattle, &Battle::quitGame);
    EndDrawing();
}

int main()
{
    InitWindow(screenWidth, screenHeight, "It Seems Unfair?!");
    SetTargetFPS(24); 

    while (!WindowShouldClose()) { //soalnya loop disini cok anj bajingan
  
        game();

    }
}
 