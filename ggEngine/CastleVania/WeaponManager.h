#pragma once
#include <ggEngine.h>"
#include "WeaponDagger.h"
#include "WeaponAxe.h"
#include "WeaponHolyWater.h"
#include "WeaponBoomerang.h"
#include "WeaponWhip.h"
#include "Simon.h"
#include "ManagerBase.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class Simon;
class WeaponManager : public ManagerBase {
public:
	WeaponManager(CVGame *cvGame);
	virtual ~WeaponManager();

	WeaponWhip* AddWeaponWhip(double x, double y, bool isLeft, Group *group);

	WeaponBase* AddWeapon(Simon *simon, double x, double y, bool isLeft, Group *group);
	WeaponDagger* AddWeaponDagger(double x, double y, bool isLeft, Group *group);
	WeaponAxe* AddWeaponAxe(double x, double y, bool isLeft, Group *group);
	WeaponHolyWater* AddWeaponHolyWater(double x, double y, bool isLeft, Group *group);
	WeaponBoomerang* AddWeaponBoomerang(double x, double y, bool isLeft, Group *group);


private:

};