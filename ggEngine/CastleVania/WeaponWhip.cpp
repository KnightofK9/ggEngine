#include "WeaponWhip.h"
#include "CVGame.h"
#include "CVDebugDefine.h"
#include "Simon.h"
#include "AudioManager.h"
#include "AnimationManager.h"


WeaponWhip::WeaponWhip(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->tag = ObjectType_Weapon;
	this->cvGame->eventManager->EnableSpriteAnimationEvent(this);
	this->SetAnchor(0.65, 0.5);
	this->SetScale(1, 1);
	this->SetVisible(false);
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(frameWidth, frameHeight);
	this->body->SetEnable(false);
	this->body->immoveable = true;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	this->body->SetLocalPosition(Vector(0, -22));
	this->events->onOverlap = [this](GameObject* go, ColliderArg e) {
		GameObject* otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag)
		{
		case ObjectType_Enemy:
#ifndef DEBUG_WHIP_NOT_HURT_ENEMY_WHEN_CONTACT
			if (otherObject) {
				EnemyBase *enemyBase = dynamic_cast<EnemyBase*>(otherObject);
				if (enemyBase->canContact)
					this->cvGame->animationManager->AddHitAnimation(otherObject->GetPosition().x, otherObject->GetPosition().y);
				enemyBase->LoseHealth(this->damage);
				this->cvGame->audioManager->onContactSound->Play();
			}
#endif // DEBUG_WHIP_NOT_HURT_ENEMY_WHEN_CONTACT

			break;

		case ObjectType_BreakableTileBrick:
		{
			ColliderArg	o = Physics::CreateOppositeColliderArg(e, this);
			otherObject->events->onCollide(otherObject, o);
			this->cvGame->audioManager->contactBreakableBrick->Play();
			this->cvGame->animationManager->AddBreakingWallAnimation(otherObject->position.x, otherObject->position.y);
		}
		break;
		case ObjectType_Candle:
			if (otherObject) {
				ColliderArg	o = Physics::CreateOppositeColliderArg(e, this);
				otherObject->events->onCollide(otherObject, o);
				this->cvGame->audioManager->onContactSound->Play();
				this->cvGame->animationManager->AddEnemyDeathAnimation(otherObject->position.x, otherObject->position.y);
				this->cvGame->animationManager->AddHitAnimation(otherObject->position.x, otherObject->position.y);
			}	
			break;
		default:
			break;
		}
	};






	//standardWhip
	this->CreateAnimation("1", { 0,1,2,2 }, false)->SetOnCompleted([this](Animator*) {
		body->SetEnable(false);
		this->SetVisible(false);
	});

	//shortWhip
	this->CreateAnimation("2", { 3,4,5,5 }, false)->SetOnCompleted([this](Animator*) {
		body->SetEnable(false);
		this->SetVisible(false);
	});

	//longWhip
	this->CreateAnimation("3", { 6,7,8,8 }, false)->SetOnCompleted([this](Animator*) {
		body->SetEnable(false);
		this->SetVisible(false);
		//this->timeInfoFlicker->Pause();
	});
	this->events->onAnimationCallBack = [this](GameObject*, AnimationArg e) {
		if ((e.frameIndex + 1) % 3 == 0) {
			body->SetEnable(true);
		}
		else {
			body->SetEnable(false);
		}
		//g_debug.Log(e.animationName + "-" + std::to_string(e.frameIndex));
	};
	//this->cvGame->physics->EnablePhysics(this);
	//this->body->CreateRectangleRigidBody(50, 50);//
	//this->body->allowGravity = false;
	//this->body->allowWorldBound = false;
	//this->body->rigidBody->SetAnchor(0.5, 0.5);
	//this->body->SetActive(false);

	//this->cvGame->eventManager->EnableSpriteAnimationEvent(this);
	//this->events->onAnimationCompleted = [this](GameObject *go, AnimationArg e) {
	//	//this->Destroy();
	//	this->SetVisible(false);
	//	//this->body->SetEnable(false);
	//	//this->ResetAnimation(e.animationName);
	//};
	this->SetWhipVersion(3);
	this->timeInfoFlicker = this->FlickeringChangeColorAnimationInfinity(5);

}


WeaponWhip::~WeaponWhip()
{
}

void WeaponWhip::SetWhipVersion(int version)
{
	this->whipVersion = version;
	this->damage = 1.0f;
	switch (this->whipVersion)
	{
	case 2:
		this->body->rigidBody->width = 30;
		this->body->rigidBody->height = 12;
		break;
	case 3:
		this->body->rigidBody->width = 36;
		this->body->rigidBody->height = 12;
		break;
	default: //version 1
		this->whipVersion = 1;
		this->damage = 0.7f;
		this->body->rigidBody->width = 30;
		this->body->rigidBody->height = 12;
		break;
	}
}

void WeaponWhip::UpgradeWhip()
{
	this->whipVersion++;
	if (this->whipVersion > 3)
		this->whipVersion = 1;
}

void WeaponWhip::Attack(bool isLeft)
{
	if (isLeft)
	{
		this->SetScale(1, 1);
		this->SetBodyAnchor(Vector(1, 0));
	}
	else {
		this->SetScale(-1, 1);
		this->SetBodyAnchor(Vector(0, 0));
	}
	
	//this->body->SetEnable(true);
	if (this->whipVersion == 3)
		this->timeInfoFlicker->Start();

	auto anim = this->PlayAnimation(std::to_string(this->whipVersion));
	this->cvGame->audioManager->usingWhipSound->Play();
	this->SetVisible(true);
}

void WeaponWhip::StandAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.9);
	this->Attack(isLeft);
}

void WeaponWhip::ClimbUpAttack(bool isLeft)
{
	this->SetAnchor(0.62, 0.9);
	this->Attack(isLeft);
}

void WeaponWhip::ClimbDownAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.98);
	this->Attack(isLeft);
}

void WeaponWhip::KneelAttack(bool isLeft)
{
	this->SetAnchor(0.64, 0.7);
	this->Attack(isLeft);
}

void WeaponWhip::Draw()
{
	CVSpriteAnimation::Draw();
}

void WeaponWhip::UpdateWorldPosition()
{
	CVSpriteAnimation::UpdateWorldPosition();
}

