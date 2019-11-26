#include "entity.h"
#include <iostream>
Entity::Entity(int mh, int h, int str, int def, int exp, int lev, int etnl, int hP, std::string n)
{
    maxHealth = mh;
    health = h;
    strength = str;
    defense = def;
    experience = exp;
    level = lev;
    experienceForNextLevel = etnl;
    healthPotions = hP;
    name = n;
}

void Entity::takeDamage(int amount){

    health -= amount;
}


