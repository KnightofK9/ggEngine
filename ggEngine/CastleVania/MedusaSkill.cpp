#include "MedusaSkill.h"
MedusaSkill::MedusaSkill(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame,image,17,10,0,2,200)
{
	CreateAnimation("move", 0, 1,true);
	this->body->allowGravity = true;
	this->body->immoveable = false;
	this->body->SetActive(true);
}

MedusaSkill::~MedusaSkill()
{
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
