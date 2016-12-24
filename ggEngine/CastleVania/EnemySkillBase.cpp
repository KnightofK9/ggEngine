#include "EnemySkillBase.h"
#include "CVGame.h"
#include "TypeEnum.h"
#include "Simon.h"
#include "TypeEnum.h"
#include "CVDebugDefine.h"
EnemySkillBase::EnemySkillBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame , int numberOfFrame , DWORD msPerFrame ) 
	: CVSpriteAnimation(cvGame,image,frameWidth,frameHeight,defaultFrame,numberOfFrame,msPerFrame)
{
	this->cvGame->physics->AttachBodyTo(this);
	this->body->CreateRectangleRigidBody(frameWidth, frameHeight);
	this->SetAnchor(0.5, 0);
	this->body->rigidBody->SetAnchor(0.5, 0);
	this->body->allowGravity = false;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	this->events->onCheckingCollide = [this](GameObject *go, ColliderArg e) {
		return OnCheckingCollide(e);
	};
	this->events->onOverlap = [this](GameObject* go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag) {
		case ObjectType_Simon:
			if (this->cvGame->simon->canContactWithEnemy)
				OnSimonContact(e);
			break;
		}
	};

	this->events->onOutOfCamera = [this](GameObject* go, EventArg e) {
		this->Destroy();
	};

	this->visible = false;
	this->body->SetEnable(false);
	this->isLeft = true;
}

EnemySkillBase::~EnemySkillBase()
{
}

void EnemySkillBase::Active()
{
	this->visible = true;
	this->body->SetEnable(true);
	this->cvGame->eventManager->EnableCameraEvent(this);
}

void EnemySkillBase::SetParentObject(EnemyBase * enemyBase)
{
	this->enemyBase = enemyBase;
}

void EnemySkillBase::Fire(bool isLeft, Vector position)
{
}



void EnemySkillBase::OnSimonContact(ColliderArg e)
{
#ifdef DEBUG_AI_SKILL_CONTACT_WITH_SIMON
	g_debug.Log(this->name + " contact with simon!");
#endif // DEBUG_AI_SKILL_CONTACT_WITH_SIMON

	this->cvGame->simon->Hurt(e.blockDirection.right);

}

bool EnemySkillBase::OnCheckingCollide(ColliderArg e)
{
	return false;
}

void EnemySkillBase::ChangeFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
	if (isLeft) {
		SetScale(1, 1);
	}
	else {
		SetScale(-1, 1);
	}
}
