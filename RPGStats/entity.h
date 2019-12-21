#include <iostream>

#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity(int mh, int h, int str, int spd = 0, int exp = 0, int lev = 1, int efnl = 200, int hP = 0, std::string n = "Enemy");
    void takeDamage(int amount);

    int getHealth(){return health;}
    void setHealth(int h){ health = h;}

    int getMaxHealth(){return maxHealth;}
    void setMaxHealth(int mh){ maxHealth = mh;}

    int getStrength(){return strength;}
    void setStrength(int str){strength = str;}

//    int getDefense(){return defense;}
//   void setDefense(int def){defense = def;}

    int getExperience(){return experience;}
    void setExperience(int exp){experience = exp;}

    int getExperienceForNextLevel(){return experienceForNextLevel;}
    void setExperienceForNextLevel(int efnl){experienceForNextLevel = efnl;}

    int getLevel(){return level;}
    void setLevel(int lvl){level = lvl;}

    int getHealthPotions(){return healthPotions;}
    void setHealthPotions(int hP){healthPotions = hP;}

    std::string getName(){ return name;}
    void setName(std::string n){name = n;}

    int getSpeed(){return speed;}
    void setSpeed(int s){speed = s;}

private:
    int maxHealth;
    int health;
    int strength;
//  int defense;
    int experience;
    int experienceForNextLevel;
    int level;
    int healthPotions;
    int speed;
    std::string name;

};

#endif // ENTITY_H
