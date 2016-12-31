#include "Boss3.h"

Boss3::Boss3(CVGame * cvGame, SpriteInfo * image, bool isPrimaryBoss) : WalkingEnemyBase(cvGame,image,16,40,0,3,200)
{
	CreateAnimation("Move", { 0,1,2,1 }, true);
	this->isPrimaryBoss = isPrimaryBoss;
	SetMoveForce(0.25);
	this->allowToDetectSimon = true;
	this->detectY = false;
}

Boss3::~Boss3()
{
}
