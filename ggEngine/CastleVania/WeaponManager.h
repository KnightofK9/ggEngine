#pragma once
#include <ggEngine.h>"
#include "WeaponDagger.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class Simon;
class WeaponManager {
public:
	WeaponManager(CVGame *cvGame);
	~WeaponManager();

	WeaponDagger* AddWeaponDagger(double x, double y, bool isLeft, Group *group);


private:
	CVGame *cvGame = nullptr;
	CVAdd *cvAdd = nullptr;
	Cache *cache = nullptr;
};