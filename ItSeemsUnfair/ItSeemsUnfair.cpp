#include <iostream>
#include <raylib.h>
#include <time.h>
#include <vector>

using namespace std;

int screenWidth = 1280;
int screenHeight = 720;

//place holder x y lokasi enemy and player 
int uiXPlayer = 150;
int uiYPlayer = 525;

int uiXCenter =320;
int uiYcenter =360;

int win = 0;
int currentLevel = 0;

//enemy special move
int lastStand = 0;
int curse = 0;

int addOnDamage = 2;

//assign class
class core {
public:
    string name;
    int level, HP, attack, heal;
    int shield_count = 0, poison_count = 0, angleRay_count = 0, realityAlter_count = 0, immortal_count = 0, raygun_count = 0; //items count

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
        DrawText(name.c_str(), _x, _y, 30, BLACK);
        DrawText(TextFormat("HP : %d", HP), _x, _y + 40, 30, DARKGRAY);
        DrawText(TextFormat("Attack : %d", attack), _x, _y + 80, 30, DARKGRAY);
        DrawText(TextFormat("Heal : %d", heal), _x, _y + 120, 30, DARKGRAY);
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

    ~playerStats(){} //destructor
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

    ~enemyStats() {} //destructor
};

class animation {
public:
    int playerX = 250;
    int playerY = 350;
    int enemyX = 950;
    int enemyY = 200;

    //Logo
    Texture2D logo;
    //DrawTexture(logo, 300, 100, WHITE);  punya draw logo

    //UI
    Texture2D stats_frame;
    Texture2D enemy_notification;
    Texture2D player_notification;


    //All Background : status not init yet
    Texture2D mainMenuBG;
    Texture2D tutorialBG;
    Texture2D level1BG;
    Texture2D level2BG;
    Texture2D level3BG;
    Texture2D level4BG;
    Texture2D level5BG;
    Texture2D finalBossBG;

    //All Effects
    Texture2D healEffect;
    Texture2D attackedEffect;

    //All Player Textures
    Texture2D playerLevel4;
    Texture2D playerLevel3;
    Texture2D playerLevel2;
    Texture2D playerLevel1;

    //All Enemy Textures
    Texture2D slime;
    Texture2D goblin;
    Texture2D goblinWarrior;
    Texture2D goblinShaman;

    animation() {
        logo = LoadTexture("Assets/Logo/logo.PNG");
        //tutorialBG = LoadTexture("Assets/Backgrounds/tutorial_bg.png");
        stats_frame = LoadTexture("Assets/UI/stats_frame.png");
        enemy_notification = LoadTexture("Assets/UI/enemy_notification.png");
        player_notification = LoadTexture("Assets/UI/player_notification.png");
        mainMenuBG = LoadTexture("Assets/Background/bg_mainMenu.png");
        level1BG = LoadTexture("Assets/Background/bg_level1.png");
        //level2BG = LoadTexture("Assets/Backgrounds/level2_bg.png");
        //level3BG = LoadTexture("Assets/Backgrounds/level3_bg.png");
        //level4BG = LoadTexture("Assets/Backgrounds/level4_bg.png");
        //level5BG = LoadTexture("Assets/Backgrounds/level5_bg.png");
        //finalBossBG = LoadTexture("Assets/Backgrounds/final_boss_bg.png");
        playerLevel4 = LoadTexture("Assets/Player/level4_player.png");
        playerLevel3 = LoadTexture("Assets/Player/level3_player.png");
        playerLevel2 = LoadTexture("Assets/Player/level2_player.png");
        playerLevel1 = LoadTexture("Assets/Player/level1_player.png");
        slime = LoadTexture("Assets/Enemy/slime_enemy.png");
        goblin = LoadTexture("Assets/Enemy/goblin_enemy.png");
        goblinWarrior = LoadTexture("Assets/Enemy/goblinWarrior_enemy.png");
        goblinShaman = LoadTexture("Assets/Enemy/goblinShaman_enemy.png");
    }

    //Draw Manager 
    void drawManager() {
        switch (currentLevel) {
        case 0:
            drawTutorial();
            break;
        case 1:
            drawlevel1_stage1();
            break;
        case 2:
            drawlevel1_stage2();
            break;
        case 3:
            drawlevel1_stage3();
            break;
        default:
            break;
        }
    }


    void drawTutorial() {

        if (win == 0) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);
            DrawText("- Tutorial Level -", 500, 675, 30, RAYWHITE);

            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            DrawTexture(slime, enemyX, enemyY, WHITE);
        }
        if (win == 1) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);
            DrawText("- Tutorial Level -", 500, 675, 30, RAYWHITE);

            DrawTexture(playerLevel4, playerX, playerY, WHITE);
        }
        if (win == 2) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);
            DrawText("- Tutorial Level -", 500, 675, 30, RAYWHITE);

            DrawTexture(slime, enemyX, enemyY, WHITE);
        }
    }

    void drawlevel1_stage1() {
        if (win == 0) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 1 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            DrawTexture(goblin, enemyX, enemyY, WHITE);
            win = 0;
        }

        if (win == 1) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 1 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            win = 0;
        }

        if (win == 2) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 1 -", 500, 675, 30, RAYWHITE);
            DrawTexture(goblin, enemyX, enemyY, WHITE);
            win = 0;
        }
  
    }

    void drawlevel1_stage2() {
        if (win == 0) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 2 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            DrawTexture(goblinWarrior, enemyX, enemyY, WHITE);
            win = 0;
        }

        if (win == 1) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 2 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            win = 0;
        }

        if (win == 2) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 2 -", 500, 675, 30, RAYWHITE);
            DrawTexture(goblinWarrior, enemyX, enemyY, WHITE);
            win = 0;
        }

    }
    void drawlevel1_stage3() {
        if (win == 0) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 3 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            DrawTexture(goblinShaman, enemyX, enemyY, WHITE);
            win = 0;
        }

        if (win == 1) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 3 -", 500, 675, 30, RAYWHITE);
            DrawTexture(playerLevel4, playerX, playerY, WHITE);
            win = 0;
        }

        if (win == 2) {
            ClearBackground(WHITE);
            DrawTexture(level1BG, 0, 0, WHITE);

            DrawText("- Level 1 . Stage 3 -", 500, 675, 30, RAYWHITE);
            DrawTexture(goblinShaman, enemyX, enemyY, WHITE);
            win = 0;
        }
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
        DrawTexture(player_notification, 390, 325, WHITE);
        DrawText(TextFormat("%s attacks %s for %d damage", player.getName().c_str(), enemy.getName().c_str(), damage), uiXCenter + 200, uiYcenter + 85, 30, BROWN);
        DrawText(TextFormat("-%d", damage), uiXCenter+595, uiYcenter-295, 30, RED);
        EndDrawing();

        WaitTime(2.0);
    }

    void slash_Enemy(playerStats& player, enemyStats& enemy) {
        int damage = enemy.getDamage();
        getSlash_Player(player, damage);

        BeginDrawing();
        DrawTexture(enemy_notification, -30, 150, WHITE);
        DrawText(TextFormat("%s attacks %s for %d damage", enemy.getName().c_str(), player.getName().c_str(), damage), uiXCenter-200, uiYcenter-90, 30, BROWN);
        DrawText(TextFormat("-%d", damage), uiXCenter-150, uiYcenter - 295, 30, RED);
        EndDrawing();

        WaitTime(2.0);
    }

    void getSlash_Player(playerStats& player, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = player.getHP();
        health -= slash;
        player.setHP(health);
    }

    void getSlash_Enemy(enemyStats& enemy, int slash) { //update health from damage received from enemy - parameter damage from enemy
        int health = enemy.getHP();
        health -= slash;
        if (lastStand == 1 && health<=0) {
            health = 1;
            lastStand = 0;

            DrawTexture(enemy_notification, -30, 150, WHITE);
            DrawText("Last Stand Activated", uiXCenter - 200, uiYcenter - 90, 30, BROWN);

            WaitTime(2.0);
        }
        enemy.setHP(health);
    }

    void slashAttack(playerStats& player, enemyStats& enemy) {
        slash_Player(player, enemy);
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
        DrawTexture(player_notification, 390, 325, WHITE);
        DrawText(TextFormat("%s is healed for %d. HP is now %d", player.getName().c_str(), healing, player.getHP()), uiXCenter + 200, uiYcenter + 85, 30, BROWN);
        EndDrawing();

        WaitTime(2.0);
    }

    void heal_Player(playerStats& player) {
        getHeal_Player(player);
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

    void interactionMenu(playerStats& player, enemyStats& enemy, int dice1, int dice2) { //Menu interaksi
        bool doneItem = 0;
        int keyPressed = 0;

        BeginDrawing();
        DrawText("Press space to roll dice!", uiXCenter + 150, uiYcenter, 30, GRAY);
        DrawText(TextFormat("Your Roll : %d | Your Enemy Roll : %d", dice1, dice2), uiXCenter + 115, uiYcenter + 80, 30, WHITE);
        DrawText("Your Chance to Attack!", uiXCenter + 115, uiYcenter + 120, 30, GREEN);

        DrawText(TextFormat("%s wants to:", player.getName().c_str()), uiXPlayer, uiYPlayer, 30, WHITE);
        DrawText("1. Slash", uiXPlayer, uiYPlayer + 40, 30, WHITE);
        DrawText("2. Heal", uiXPlayer, uiYPlayer + 80, 30, WHITE);
        DrawText(TextFormat("3. Item (%d)", itemAvail()), uiXPlayer, uiYPlayer + 120, 30, WHITE);
        EndDrawing();
        
        if (IsKeyPressed(KEY_ONE)) {
            keyPressed = 1;            
        }
        if (IsKeyPressed(KEY_TWO)) {
            keyPressed = 2;
        }
        if (IsKeyPressed(KEY_THREE)) {
            keyPressed = 3;
        }

        if (keyPressed == 1) {
            slash_Player(player, enemy);
            keyPressed = 0;
        }
        else if (keyPressed == 2) {
            heal_Player(player);
            keyPressed = 0;
        }
        else if (keyPressed == 3) {
            if (itemAvail() == 1 && doneItem == 0) {
                this->itemPick(); //cuman bisa sekali && ketika punya item doang baru bisa akses
                doneItem = 1;
            }
            else {
                BeginDrawing();
                DrawText("Items are not Available", uiXCenter + 70, uiYcenter + 40, 30, WHITE);
                EndDrawing();

                WaitTime(1.5);
                keyPressed = 0;
               
            }
            interactionMenu(player, enemy,dice1,dice2);
        }
        else {
            interactionMenu(player, enemy,dice1,dice2);
        }
    }

    void enemyLogic(playerStats& player, enemyStats& enemy) {
        slash_Enemy(player, enemy);

        BeginDrawing();
        DrawText(TextFormat("%s wants to Attack (-%d)", enemy.getName().c_str(), enemy.getDamage()), uiXCenter - 130, uiYcenter - 100, 30, WHITE);
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
            drawManager(); //diganti sama void drawLevel (ada level selectornya)
            BeginDrawing();
            DrawTexture(stats_frame, -50, -20, WHITE);
            DrawTexture(stats_frame, 700, -20, WHITE);
            player.checkStats(50, 25);
            enemy.checkStats(800, 25);
            DrawText("Press space to roll dice!", uiXCenter + 150, uiYcenter, 30, WHITE);
            EndDrawing();
        }
        else {
            dice1 = (rand() % 6) + 1;//visual untuk dice1
            dice2 = (rand() % 6) + 1;//visual untuk dice2

            DrawText(TextFormat("Your Roll : %d | Your Enemy Roll : %d", dice1, dice2), uiXCenter + 115, uiYcenter + 80, 30, WHITE);
            

            if (dice1 > dice2) {
                
                //WaitTime(2.0);
                interactionMenu(player, enemy,dice1,dice2);
            }
            else if (dice1 < dice2) {

                if (curse == 1) {
                    enemy.attack += addOnDamage;

                    DrawText("Shaman's Curse is Growling!", uiXCenter + 500, 200, 25, RED);
                }

                BeginDrawing();
                DrawText("Press space to roll dice!", uiXCenter + 150, uiYcenter, 30, GRAY);
                DrawText("Enemy's Chance to Attack!", uiXCenter + 115, uiYcenter + 120, 30, RED);
                EndDrawing();

                WaitTime(2.0);

                enemyLogic(player, enemy);
            }
            else if (dice1 == dice2) {
                BeginDrawing();
                DrawText("Press space to roll dice!", uiXCenter + 150, uiYcenter, 30, GRAY);
                DrawText("Tie!", uiXCenter + 115, uiYcenter + 130, 30, BLUE);
                EndDrawing();

                WaitTime(2.0);
                isSpacePressed = 1;
            }
        }
    }

    void battle(playerStats& player, enemyStats& enemy) { // battle begins lol

        getMaxHP(player, enemy); // get max HP

        while (player.getHP() > 0 && enemy.getHP() > 0) {
            diceBattle(player, enemy);
        }

        if (player.getHP() <= 0) {

            win = 2;
            drawManager();

            BeginDrawing();
            DrawText(TextFormat("%s has been defeated.", player.getName().c_str()), screenWidth / 2 - MeasureText(TextFormat("%s has been defeated.", player.getName().c_str()), 60) / 2, screenHeight / 2 - 50, 60, RED);
            EndDrawing();

            WaitTime(5.0);
            levelManager();
        }

        if (enemy.getHP() <= 0) {
            
            win = 1;
            drawManager();
            BeginDrawing();
            

            DrawText(TextFormat("%s has been defeated.", enemy.getName().c_str()), screenWidth / 2 - MeasureText(TextFormat("%s has been defeated.", enemy.getName().c_str()), 60) / 2, screenHeight / 2 - 50, 60, YELLOW);
            EndDrawing();

            WaitTime(5.0);

            currentLevel++;
            levelManager();
        }
    }


    void levelManager() {

        switch (currentLevel) {
        case 0:
            tutorial();
            break;
        case 1:
            level1_stage1();
            break;
        case 2:
            lastStand = 1;
            level1_stage2();
            break;
        case 3:
            curse = 1;
            level1_stage3();
            curse = 0;
            break;
        default:
            break;
        }
    }

    //levels : tutorial
    void tutorial() {

        playerStats player("Ralph", 60, 40, 10, 10);
        enemyStats slime("Tutorial Slime", 1, 2, 2, 1);
        
        BeginDrawing();
        drawTutorial();
        battle(player, slime);
        EndDrawing();
    }

    //transisi dr tutorial ke level 1 - 2

    void level1_stage1() {

        playerStats player("Ralph", 60, 40, 10, 10);
        enemyStats enemy("Goblin", 1, 15, 5, 0);

        BeginDrawing();
        drawlevel1_stage1();
        battle(player, enemy);
        EndDrawing();

    }

    void level1_stage2() {
        playerStats player("Ralph", 60, 40, 10, 10);
        enemyStats enemy("Goblin Warrior", 1, 15, 15, 0);

        BeginDrawing();
        drawlevel1_stage2();
        battle(player, enemy);
        EndDrawing();
    }

    void level1_stage3() {
        playerStats player("Ralph", 60, 40, 10, 10);
        enemyStats enemy("Goblin Shaman", 1, 37, 7, 7);

        BeginDrawing();
        drawlevel1_stage3();
        battle(player, enemy);
        EndDrawing();
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
    CloseWindow();  // This will close the window and exit the application
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

    currentLevel = 0;

    Battle startBattle;
    animation startanimation;

    Vector2 mousePosition = GetMousePosition();
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;

    BeginDrawing();
    DrawTexture(startanimation.mainMenuBG, 0, 0, WHITE);
    DrawTexture(startanimation.logo, 300, 50, WHITE);
    DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 70) / 2 - 300, screenHeight / 2 + 40, 70, GOLD);
    createText("o> Start Game", screenWidth / 2 - MeasureText("o> Start Game", 30) / 2 - 370, screenHeight / 2 + 120, 30, WHITE, mouseX, mouseY, &startBattle, &Battle::levelManager);
    createText("o> Quit", screenWidth / 2 - MeasureText("o> Quit", 30) / 2 - 427, screenHeight / 2 + 160, 30, WHITE, mouseX, mouseY, &startBattle, &Battle::quitGame);
    EndDrawing();
}

int main()
{
 
    InitWindow(screenWidth, screenHeight, "It Seems Unfair?! - Ignasius Deva 5024231003");
    SetTargetFPS(30);


    while (!WindowShouldClose()) {

        game();

        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();

        }

    }
}