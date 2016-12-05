#pragma once
#include <ggEngine.h>"
#include "WeaponDagger.h"
#include "WeaponAxe.h"
#include "WeaponHolyWater.h"
#include "WeaponBoomerang.h"
#include "WeaponWhip.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class Simon;
class WeaponManager {
public:
	WeaponManager(CVGame *cvGame);
	virtual ~WeaponManager();

	WeaponWhip* AddWeaponWhip(double x, double y, bool isLeft, int version, Group *group);

	WeaponDagger* AddWeaponDagger(double x, double y, bool isLeft, Group *group);
	WeaponAxe* AddWeaponAxe(double x, double y, bool isLeft, Group *group);
	WeaponHolyWater* AddWeaponHolyWater(double x, double y, bool isLeft, Group *group);
	WeaponBoomerang* AddWeaponBoomerang(double x, double y, bool isLeft, Group *group);


private:
	CVGame *cvGame = nullptr;
	CVAdd *cvAdd = nullptr;
	Cache *cache = nullptr;
};