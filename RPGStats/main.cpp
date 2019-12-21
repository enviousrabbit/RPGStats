/**
  Todo

  You need to get the leveling numbers right some how.
  You'll want to take a more methodical approach then just
  screwing around with numbers.



#ifdef __linux__
    //linux code goes here
    std::cout << "You're on linux!\n";
#elif _WIN32
    // windows code goes here
    std::cout << "You're on Windows.\n";
#else

    std::cout << "What the hell are you on!\n";
#endif
    int a;
    std::cin >> a;
    return 0;


  **/


#include <cstdlib>
#include <iostream>
#include <ctime>
#include "entity.h"

#ifdef _WIN32
#include <windows.h>
#endif




const int SKILLINCREASESTRENGTH = 2;
//const int SKILLINCREASEDEFENSE = 2;
const int SKILLINCREASESPEED = 3;
const int SKILLINCREASEHEALTH = 1;



const int EnemyStartingMaxHealth = 1;
const int EnemyStartingHealth = 1;
const int EnemyStartingStrength = 1;
//const int EnemyStartingDefense = 0;
const int EnemyStartingSpeed = 0;
const int EnemyStartingExperience = 5;
const int EnemyIncreaseInExperience = 0;
const int EnemyStartingSkillPoints = 0;
const int EnemyIncreaseInSkillPoints = 5;
const int EnemyStartingPlace = 1;
const int EnemyStartingLevel = 1;


const int PLAYERSKILLPOINTS = 5;
const int PlayerIncreaseInNextLevelExperience = 0;
const int PlayerStartingInNextLevelExperience = 5;
const int PlayerStartingExperience = 5;
const int PlayerStartingLevel = 1;
const int PlayerStartingHealth = 1;
const int PlayerStartingStrength = 1;
//const int PlayerStartingDefense = 1;
const int PlayerStartingPotions = 1;
const int PlayerStartingSpeed = 0;
const int turnsBeforePotion = 3;

int game();

int war(Entity& player);
int battle(Entity &e, Entity &enemy);
Entity chooseStats();
void increaseStats(Entity& e, Entity& enemy);
int increaseStat(Entity& e, char a, int skillpoints);
void levelUp(Entity& e, Entity& enemy);
Entity setRandomStats(int battlesFought);
void attackFromTo(Entity& e1, Entity& e2);

void useHealthPotion(Entity& e);
Entity createEnemy(int battlesFought);
int checkBattleState(Entity& player, Entity& enemy);


void checkInput(){
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(256,'\n');
    }
}

void fixInput(){
    std::cin.clear();
    std::cin.ignore(256,'\n');
}


void clearScreen(){


#ifdef __linux__
    //linux code goes here
    std::cout << "\033[2J\033[1;1H";
#elif _WIN32
    // windows code goes here
    COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
#else

    std::cout << "What the hell are you on!\n";
#endif

}

void pause(){
    std::cout << "Enter Anything: ";
    int a;
    std::cin >> a;
    checkInput();
}






void printStats(Entity& e){
    std::cout << e.getName() << "---------------------------------\n" << "Max Health: " << e.getMaxHealth() << ", Health: " << e.getHealth() << ", str: " << e.getStrength() << ", spd: " << e.getSpeed()
    << ", lvl: " << e.getLevel()  << ", Exp: " << e.getExperience() << ", Experience for next level: " << e.getExperienceForNextLevel()
    << ", Potions: " << e.getHealthPotions() << '\n';
}




int main()
{

    return game();
}

int game(){

    std::srand(std::time(nullptr));
    Entity player(PlayerStartingHealth, PlayerStartingHealth, PlayerStartingStrength, PlayerStartingSpeed, PlayerStartingExperience,
                  PlayerStartingLevel, PlayerStartingInNextLevelExperience, PlayerStartingPotions, "Player");








    clearScreen();

    int battlesFought = war(player);
    clearScreen();
    std::cout << "Final Player Stats.\n";
    printStats(player);
    std::cout << "Battles Won: " << battlesFought << std::endl;
    pause();







    return 0;
}



int war(Entity& player){

    //Initiliaze War
    int battlesFought = 0;


    //War loop
    while(true){

       Entity enemy = createEnemy(battlesFought);
       if(player.getExperience() >= player.getExperienceForNextLevel()){
           levelUp(player, enemy);
       }
       printStats(player);
       if(battle(player, enemy) == 1) break;
       battlesFought++;
       clearScreen();

    }
    //War lost
    return battlesFought;
}



int battle(Entity &player, Entity &enemy){

    clearScreen();
    std::cout << "Battle Start!\n";

    printStats(enemy);
    printStats(player);

    pause();

    //First Turn
    clearScreen();

    int turn = 0;

    // If player is faster player attacks first
    if(player.getSpeed() > enemy.getSpeed()){
        std::cout << player.getName() << " attacks first!\n";
        attackFromTo(player,enemy);
        printStats(enemy);
        printStats(player);
        //Change so that it is the enemies turn next.
        turn = 2;
        pause();





    }
    // If enemy is faster enemy attacks first
    else if(enemy.getSpeed() > player.getSpeed()){
        std::cout << enemy.getName() << " attacks first!\n";
        attackFromTo(enemy,player);
        printStats(enemy);
        printStats(player);
        //Change so that it is the player's turn next.
        turn = 1;
        pause();



    }

    int state = checkBattleState(player, enemy);
    if( state < 2){
        return state;
    }

    while(true){
        clearScreen();

         std::cout << "Attack!\n";

         //Enemies Turn
         attackFromTo(enemy, player);


         //Players Turn
         attackFromTo(player,enemy);








        printStats(enemy);
        printStats(player);
        pause();
        int state = checkBattleState(player, enemy);

        if( state < 2){
            return state;
        }

    }

}




void attackFromTo(Entity& e1, Entity& e2){
    e2.takeDamage(e1.getStrength());
}

int checkBattleState(Entity& player, Entity& enemy){
    if(player.getHealth() <= 0){

        std::cout << "You Died!\n";
        pause();
        return 1;

    }
    else if(enemy.getHealth() <= 0){
     std::cout << "You defeated the enemy!\n";
     //Adds the enemy's experience to the players experience
     player.setExperience(player.getExperience() + enemy.getExperience());

     pause();
     return 0;
    }
    return 2;


}


void increaseStats(Entity& e, Entity& enemy){
    e.setHealth(e.getMaxHealth());

    //There are modifiers to i within the for loop
    int SkillPointsLeft = PLAYERSKILLPOINTS;
    while(SkillPointsLeft != 0){

    clearScreen();

    std::cout << "Next Enemy Stats Below\n";

    printStats(enemy);
    printStats(e);
    std::cout << "Remaining skill points: " << SkillPointsLeft << '\n';
    std::cout << "Enter h for health, s for strength, or f for speed\n";
    char a;
    std::cin >> a;
    checkInput();
    int PreSkillPoints = SkillPointsLeft;
    SkillPointsLeft = increaseStat(e, a, SkillPointsLeft);
    if(SkillPointsLeft == PreSkillPoints){


        std::cout << "Try again.\n";
        pause();
    }

    }





}

int increaseStat(Entity& e, char a, int skillpoints){





    switch (a) {
    case 'h':
        if(skillpoints >= SKILLINCREASEHEALTH){
        e.setMaxHealth(e.getMaxHealth() + 1);
        e.setHealth(e.getMaxHealth());
        return skillpoints - SKILLINCREASEHEALTH;
        }

        break;
    case 's':
        if(skillpoints >= SKILLINCREASESTRENGTH){
        e.setStrength(e.getStrength() + 1);
        return skillpoints - SKILLINCREASESTRENGTH;
        }

        break;
    case 'f':
        if(skillpoints >= SKILLINCREASESPEED){
        e.setSpeed(e.getSpeed() + 1);
        return skillpoints - SKILLINCREASESPEED;
        }
        break;

    default:

        return skillpoints;
    }

    return skillpoints;
}


void levelUp(Entity& e, Entity& enemy){
    increaseStats(e, enemy);
    e.setLevel(e.getLevel() + 1);
    e.setExperience(e.getExperience() - e.getExperienceForNextLevel());
    e.setExperienceForNextLevel(e.getExperienceForNextLevel() + PlayerIncreaseInNextLevelExperience);
}

Entity createEnemy(int battlesFought){
    Entity enemy = setRandomStats(battlesFought);




    return enemy;
}

Entity setRandomStats(int battlesFought){
    int skillPoints = EnemyStartingSkillPoints + ((battlesFought + EnemyStartingPlace) * EnemyIncreaseInSkillPoints);


    int a;
    Entity e{EnemyStartingMaxHealth,EnemyStartingHealth,EnemyStartingStrength,EnemyStartingSpeed,
                EnemyStartingExperience, battlesFought + EnemyStartingLevel,2000};

    e.setExperience(e.getExperience() + (EnemyIncreaseInExperience * battlesFought));
    int skillPointsLeft = skillPoints;
    while(skillPointsLeft != 0){

    a = (rand() + 1)%3;

    switch (a) {
    case 0:
        skillPointsLeft = increaseStat(e, 'h', skillPointsLeft);


        break;
    case 1:
        skillPointsLeft = increaseStat(e, 's', skillPointsLeft);

        break;
    case 2:
        skillPointsLeft = increaseStat(e, 'f', skillPointsLeft);

        break;
    default:
        std::cout << "Something Went Wrong in SetRandomStats";
        pause();

    }
    }
    return e;
}

void useHealthPotion(Entity& e){
    int healthIncrease = e.getMaxHealth()/2;
    if(healthIncrease + e.getHealth() > e.getMaxHealth()){
        e.setHealth(e.getMaxHealth());
    }
    else{
    e.setHealth(e.getHealth() + healthIncrease);
    }
    e.setHealthPotions(e.getHealthPotions() - 1);

}
