#pragma once
#include "SkilledHero.h"

class BladestormHero : public SkilledHero {
	// TODO
public:
    BladestormHero(Hero* a): SkilledHero(a){ }
    void getSkill(name2Level& skillMap){
        skillMap["Bladestorm"]++;
        base->getSkill(skillMap);
    }
};
