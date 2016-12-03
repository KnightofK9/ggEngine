#include "WeaponStopWatch.h"
#include "CVAdd.h"

WeaponStopWatch::WeaponStopWatch(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame, image)
{

}

WeaponStopWatch::~WeaponStopWatch()
{
	//g_debug.Log("Deleting WeaponStopWatch");
}



void WeaponStopWatch::FireWeapon(bool isLeft)
{
	Simon *simon = this->cvGame->simon;
	if (simon->GetHeartPoint() - this->heartConsumtion >= 0)
	{
		simon->DecreaseHeartPoint(this->heartConsumtion);
	}
}