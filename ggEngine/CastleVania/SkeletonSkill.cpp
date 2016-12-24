#include "SkeletonSkill.h"

SkeletonSkill::SkeletonSkill(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame,image,15,16,0,3,50)
{
	CreateAnimation("move", 0, 2, true);
	this->fireSpeed = 2.0;
	this->body->allowGravity = true;
	this->body->immoveable = false;
	this->body->SetActive(true);
}

SkeletonSkill::~SkeletonSkill()
{
}

void SkeletonSkill::Active()
{
	EnemySkillBase::Active();
	PlayAnimation("move");
}

EnemySkillBase * SkeletonSkill::GetBulletInstance()
{
	auto go = new SkeletonSkill(this->cvGame, this->image);
	AddBulletToGroup(go);
	return go;
}
void SkeletonSkill::Fire(bool isLeft, Vector position)
{
	int modifier = 1;
	if (isLeft) modifier = -1;
	EnemySkillBase* go = GetBulletInstance();
	go->SetPosition(position);
	go->UpdateWorldPosition();
	go->body->PreUpdate();
	go->ChangeFacingDirection(isLeft);
	go->body->SetForce(this->fireSpeed, Vector(modifier/2.0, -1));
	go->Active();
}
