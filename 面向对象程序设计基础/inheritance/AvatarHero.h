#pragma once
#include "SkilledHero.h"

class AvatarHero : public SkilledHero {
	// TODO
public:
    AvatarHero(Hero* a) : SkilledHero(a){ }
    void getSkill(name2Level& skillMap){
        skillMap["Avatar"]++;
        base->getSkill(skillMap);
    }
};
