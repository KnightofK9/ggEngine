#include "ManagerBase.h"

ManagerBase::ManagerBase(CVGame * cvGame)
{
	this->cvGame = cvGame;
	this->preload = cvGame->preload;
	this->add = cvGame->add;
	this->cache = cvGame->cache;
}

ManagerBase::~ManagerBase()
{
}
