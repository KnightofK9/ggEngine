#include "WeaponManager.h"
#include "CVGame.h"
#include "CVAdd.h"
WeaponManager::WeaponManager(CVGame * cvGame)
{
	this->cvGame = cvGame;
	this->cvAdd = cvGame->cvAdd;
	this->cache = cvGame->cache;
}

WeaponManager::~WeaponManager()
{
}
