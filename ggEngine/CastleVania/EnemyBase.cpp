#include "EnemyBase.h"
#include "Simon.h"
EnemyBase::EnemyBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image, frameWidth,frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::CheckCollisionToSimon(Simon * simon)
{
}

void EnemyBase::OnSimonContact(Simon * simon, ColliderArg e)
{
}

void EnemyBase::Destroy()
{
}

void EnemyBase::Active()
{
}
