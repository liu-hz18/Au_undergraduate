#pragma once
#include "Hero.h"

class SkilledHero : public Hero {
	// TODO
public:
    Hero* base;    
    SkilledHero(Hero* a):base(a){ }
    void getSkill(name2Level& skillMap){ }
};
