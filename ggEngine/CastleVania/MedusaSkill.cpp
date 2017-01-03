#include "MedusaSkill.h"
#include "TypeEnum.h"
#include "Simon.h"
MedusaSkill::MedusaSkill(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame,image,17,10,0,2,200)
{
	CreateAnimation("move", 0, 1,true);
	this->body->allowGravity = true;
	this->body->immoveable = false;
	this->body->SetPhysicsMode(PhysicsMode_AABBSweptMix);
	this->body->SetActive(true);
	//this->events->onCollide = [this](GameObject* go, ColliderArg e) {
	//	auto otherObject = e.colliderObject;
	//	Tag tag = otherObject->tag;
	//	switch (tag) {
	//	case ObjectType_Simon:
	//		//if (this->cvGame->simon->canContactWithEnemy)
	//			OnSimonContact(e);
	//		break;
	//	case ObjectType_Weapon:
	//	case ObjectType_SubWeapon:
	//		this->Destroy();
	//		break;
	//	}
	//};
}

MedusaSkill::~MedusaSkill()
{
}

void MedusaSkill::Active()
{
	EnemySkillBase::Active();
	this->PlayAnimation("move");
}

EnemySkillBase * MedusaSkill::GetBulletInstance()
{
	auto go = new MedusaSkill(this->cvGame, this->image);
	AddBulletToGroup(go);
	return go;
}

bool MedusaSkill::OnCheckingCollide(ColliderArg e)
{
	Tag tag = e.colliderObject->tag;
	switch (tag) {
	case ObjectType_LevelTwoBrick:
		if (e.blockDirection.down) return true;
		break;
	}
	return false;
}

void MedusaSkill::ChangeFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
	if (isLeft) {
		SetScale(-1, 1);
	}
	else {
		SetScale(1, 1);
	}
}
