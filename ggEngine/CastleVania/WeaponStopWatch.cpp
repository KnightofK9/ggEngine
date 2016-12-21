#include "WeaponStopWatch.h"
#include "CVAdd.h"

WeaponStopWatch::WeaponStopWatch(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{

}

WeaponStopWatch::~WeaponStopWatch()
{
	//g_debug.Log("Deleting WeaponStopWatch");
}



void WeaponStopWatch::FireWeapon(bool isLeft)
{
}