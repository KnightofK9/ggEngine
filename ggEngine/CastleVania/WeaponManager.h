#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class CVAdd;
class WeaponManager {
public:
	WeaponManager(CVGame *cvGame);
	~WeaponManager();
private:
	CVGame *cvGame = nullptr;
	CVAdd *cvAdd = nullptr;
	Cache *cache = nullptr;
};