/**
  Todo

  You need to get the leveling numbers right some how.
  You'll want to take a more methodical approach then just
  screwing around with numbers.



  **/


#include <cstdlib>
#include <iostream>
#include <ctime>
#include "entity.h"

const int SKILLPOINTS = 4;

const int SKILLINCREASESTRENGTH = 3;
const int SKILLINCREASEDEFENSE = 2;
const int SKILLINCREASEHEALTH = 6;



const int EnemyStartingMaxHealth = 1;
const int EnemyStartingHealth = 1;
const int EnemyStartingStrength = 1;
const int EnemyStartingDefense = 0;
const int EnemyStartingExperience = 5;
const int EnemyIncreaseInExperience = 0;
const int EnemyStartingSkillPoints = 0;
const int EnemyIncreaseInSkillPoints = 1;

const int PlayerIncreaseInNextLevelExperience = 5;
const int PlayerStartingHealth = 6;
const int PlayerStartingStrength = 1;
const int PlayerStartingDefense = 1;
const int PlayerStartingPotions = 1;
const int turnsBeforePotion = 3;

int game();

int war(Entity& player);
int battle(Entity &e, Entity &enemy, int battlesFought);
Entity chooseStats();
void increaseStats(Entity& e, Entity& enemy);
void levelUp(Entity& e, Entity& enemy);
Entity setRandomStats(int battlesFought);

void useHealthPotion(Entity& e);
Entity createEnemy(int battlesFought);



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
    std::cout << "\033[2J\033[1;1H";
}

void pause(){
    std::cout << "Enter Anything: ";
    int a;
    std::cin >> a;
    checkInput();
}






void printStats(Entity& e){
    std::cout << e.getName() << "---------------------------------\n" << "Max Health: " << e.getMaxHealth() << ", Health: " << e.getHealth() << ", str: " << e.getStrength() << ", def: " << e.getDefense()
    << ", lvl: " << e.getLevel()  << ", Exp: " << e.getExperience() << ", Experience for next level: " << e.getExperienceForNextLevel()
    << ", Potions: " << e.getHealthPotions() << '\n';
}




int main()
{

    return game();
}

int game(){


    Entity player = chooseStats();
    std::cout << "Player \n"; printStats(player);



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
    int battlesFought = 0;
    while(true){
      if(battlesFought != 0){
          if(battlesFought%turnsBeforePotion == 0){
               clearScreen();
               std::cout << "You got a potion\n";
               player.setHealthPotions(player.getHealthPotions() + 1);
               pause();
         }
      }

       Entity enemy = createEnemy(battlesFought);

       std::cout << "Next Enemy Stats Below.\n";
       printStats(enemy);
       pause();
       if(player.getExperience() >= player.getExperienceForNextLevel()){

           levelUp(player, enemy);
       }
       printStats(player);
       if(player.getHealthPotions() >= 1){
        while(true){
       clearScreen();
       std::cout << "Next Enemy Stats Below.\n";
                    printStats(enemy);
                    printStats(player);
       std::cout << "-----------------------\n" << "Use Health Potion?(Heals half of max health)\n"
                 << "Enter y for yes or n for no: ";
       char answer;
       std::cin >> answer;
       bool breakOut = false;
       switch(answer){
       case 'y':
           useHealthPotion(player);
           breakOut = true;
           break;
       case 'n':
           breakOut = true;
           break;
       default:
           fixInput();
           break;

       }
       fixInput();
       if(breakOut){
        break;
       }
       }
       }
       if(battle(player, enemy, battlesFought) == 1) break;
       battlesFought++;
       clearScreen();

    }
    return battlesFought;
}

int battle(Entity &player, Entity &enemy, int battlesFought){
    int damage = 0;
    clearScreen();
    std::cout << "Battle Start!\n";

    printStats(enemy);
    printStats(player);

    pause();
    while(true){
        clearScreen();
        std::cout << "\n";
        //Enemies Turn
        damage = enemy.getStrength() - player.getDefense();
        if(damage < 1){
            enemy.takeDamage((-1 * damage) + 1);
            damage = 1;
        }
        player.takeDamage(damage);
        //Players Turn
        damage = player.getStrength() - enemy.getDefense();
        if(damage < 1){
            player.takeDamage((-1 * damage) + 1);
            damage = 1;
        }
        enemy.takeDamage(damage);


        printStats(enemy);
        printStats(player);
        pause();

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


    }

}

Entity chooseStats(){
    int health = PlayerStartingHealth;
    int maxHealth = PlayerStartingHealth;
    int strength = PlayerStartingStrength;
    int defense = PlayerStartingDefense;


    int skillPoints = SKILLPOINTS;
    std::cout << "You have " << skillPoints << " skill points\n"
    << "You can use 1 skill point to get " << SKILLINCREASEHEALTH << " health, " << SKILLINCREASESTRENGTH
    << " strength, or " << SKILLINCREASEDEFENSE << " defense\n";
    pause();

    char a;
    for(int i = 0; i < SKILLPOINTS;  i++){
    clearScreen();
    std::cout << "You currently have: " << maxHealth << " Health, " << strength << " Strength, and " << defense << " Defense.\n"
    << "Enter h for health, s for strength, or d for defense\n";
    std::cin >> a;
    checkInput();

    switch (a) {
    case 'h':
        maxHealth += SKILLINCREASEHEALTH;
        health += SKILLINCREASEHEALTH;
        fixInput();
        break;
    case 's':
        strength += SKILLINCREASESTRENGTH;
        fixInput();
        break;
    case 'd':
        defense += SKILLINCREASEDEFENSE;
        fixInput();
        break;
    default:
        std::cout << "Try again.\n";
        fixInput();
        i -= 1;
    }

    }

    return Entity(maxHealth, health, strength, defense, 0, 1, 10, PlayerStartingPotions, "Player");

}

void increaseStats(Entity& e, Entity& enemy){
    e.setHealth(e.getMaxHealth());
    char a;
    for(int i = 0; i < SKILLPOINTS;  i++){
    clearScreen();
    std::cout << "Next Enemy Stats Below\n";
    printStats(enemy);
    printStats(e);
    std::cout << SKILLPOINTS - i << " skill points left.\n";
    std::cout << "Enter h for health, s for strength, or d for defense\n";
    std::cin >> a;
    checkInput();
    switch (a) {
    case 'h':
        e.setMaxHealth(e.getMaxHealth() + SKILLINCREASEHEALTH);
        e.setHealth(e.getMaxHealth());


        break;
    case 's':
        e.setStrength(e.getStrength() + SKILLINCREASESTRENGTH);
        break;
    case 'd':
        e.setDefense(e.getDefense() + SKILLINCREASEDEFENSE);
        break;
    default:
        std::cout << "Try again.\n";
        i -= 1;
    }

    }

    e.setLevel(e.getLevel() + 1);
    e.setExperience(e.getExperience() - e.getExperienceForNextLevel());
    e.setExperienceForNextLevel(e.getExperienceForNextLevel() + PlayerIncreaseInNextLevelExperience);


}


void levelUp(Entity& e, Entity& enemy){
    std::cout << "Level Up!\n";
    pause();
    increaseStats(e, enemy);
}

Entity createEnemy(int battlesFought){
    Entity enemy = setRandomStats(battlesFought);




    return enemy;
}

Entity setRandomStats(int battlesFought){
    int skillPoints = EnemyStartingSkillPoints + (battlesFought * EnemyIncreaseInSkillPoints);


    int a;
    Entity e{EnemyStartingMaxHealth,EnemyStartingHealth,EnemyStartingStrength,EnemyStartingDefense,
                EnemyStartingExperience,battlesFought,2000};

    e.setExperience(e.getExperience() + (EnemyIncreaseInExperience * battlesFought));
    for(int i = 0; i < skillPoints; i++){
    a = rand()%3;
    switch (a) {
    case 0:
        e.setMaxHealth(e.getMaxHealth() + SKILLINCREASEHEALTH);
        e.setHealth(e.getMaxHealth());


        break;
    case 1:
        e.setStrength(e.getStrength() + SKILLINCREASESTRENGTH);
        break;
    case 2:
        e.setDefense(e.getDefense() + SKILLINCREASEDEFENSE);
        break;
    default:
        std::cout << "Something Went Wrong in SetRandomStats";
        pause();
        i -= 1;
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
