#include "WeaponBase.h"
#include "CVGame.h"
#include "CVDebugDefine.h"
#include "AudioManager.h"
#include "AnimationManager.h"
#include "EnemyBase.h"
#include "Simon.h"
WeaponBase::WeaponBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->SetAnchor(0.5, 0.5);
	this->cvGame = cvGame;
	//this->cvGame->physics->EnablePhysics(this);
	this->cvGame->physics->AttachBodyTo(this);
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	this->body->CreateRectangleRigidBody(frameWidth, frameHeight);
	this->body->allowGravity = true;
	this->body->syncBounds = false;
	this->body->rigidBody->SetAnchor(0.5, 0.5);
	this->tag = ObjectType_Weapon;

	this->events->onCheckingCollide = [this](GameObject *go, ColliderArg e) {
		return OnCheckingCollide(e);
	};
	this->events->onOverlap = [this](GameObject *go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag) {
		case ObjectType_Enemy:
			if (otherObject)
				OnEnemyContact(dynamic_cast<EnemyBase*>(otherObject), e);
			break;

		case ObjectType_Static:
			OnStaticContact(otherObject,e);
			break;

		case ObjectType_LevelTwoBrick:
			OnBrickContact(otherObject, e);
			break;

		case ObjectType_Candle:
			if (otherObject)
				OnCandleContact(otherObject, e);
			break;

		case ObjectType_Simon:
			OnSimonContact(e);
			break;

		default:
			break;
		}
	};
	
	this->visible = false;
	this->body->SetActive(false);
}

WeaponBase::~WeaponBase()
{
	//g_debug.Log("Deleting WeaponBase");
}

void WeaponBase::FireWeapon(bool isLeft)
{
}

void WeaponBase::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
#ifdef DEBUG_SHOW_LOG_WHEN_WEAPON_CONTACT_ENEMY
	g_debug.Log("Weapon contacted enemy!!!");
#endif //DEBUG_SHOW_LOG_WHEN_WEAPON_CONTACT_ENEMY
	
#ifndef DEBUG_SUBWEAPON_NOT_HURT_ENEMY_WHEN_CONTACT
	if (dynamic_cast<AI7*>(enemyBase) != nullptr)
		return;
	enemyBase->LoseHealth(this->damage);
	this->cvGame->audioManager->onContactSound->Play();
	this->cvGame->animationManager->AddHitAnimation(enemyBase->position.x, enemyBase->position.y);
#endif // DEBUG_SUBWEAPON_NOT_HURT_ENEMY_WHEN_CONTACT
}

void WeaponBase::OnOutOfCamera(EventArg e)
{
	//g_debug.Log("Out of camera!");
	this->Destroy();
}

void WeaponBase::OnSimonContact(ColliderArg e)
{
#ifdef DEBUG_SHOW_LOG_WHEN_WEAPON_CONTACT_SIMON
	g_debug.Log("Contact simon!");
#endif //DEBUG_SHOW_LOG_WHEN_WEAPON_CONTACT_SIMON

}

void WeaponBase::OnStaticContact(GameObject * staticObject, ColliderArg e)
{
	this->Destroy();
}

void WeaponBase::OnBrickContact(GameObject * brick, ColliderArg e)
{

}

void WeaponBase::OnCandleContact(GameObject * candle, ColliderArg e)
{
	ColliderArg	o = Physics::CreateOppositeColliderArg(e, this);
	candle->events->onCollide(candle, o);
	this->cvGame->audioManager->onContactSound->Play();
	this->cvGame->animationManager->AddEnemyDeathAnimation(candle->position.x, candle->position.y);
	this->cvGame->animationManager->AddHitAnimation(candle->position.x, candle->position.y);
}

void WeaponBase::Destroy()
{
	GameObject::Destroy();
}

bool WeaponBase::OnCheckingCollide(ColliderArg e)
{
	return false;
}

void WeaponBase::Active()
{
	this->cvGame->eventManager->EnableCameraEvent(this);
	this->events->onOutOfCamera = [this](GameObject *go, EventArg e) {
		OnOutOfCamera(e);
	};
	this->visible = true;
	this->body->SetActive(true);
}

Vector WeaponBase::GetHorizontalDirection(bool isLeft)
{
	Vector direction(-1, 0);
	if (!isLeft) {
		direction.x = 1;
	}
	return direction;
}

void WeaponBase::FireHorizontal(bool isLeft, double throwForce)
{
	if (isLeft) {
		this->SetScale(-1, 1);
	}
	Vector direction = GetHorizontalDirection(isLeft);
	this->body->AddForce(throwForce, direction);
}

Vector WeaponBase::GetThrowDirection(bool isLeft)
{
	Vector direction(-1, -2);
	if (!isLeft) {
		direction.x = 1;
	}
	return direction;
}

void WeaponBase::FireAsThrow(bool isLeft, double throwForce)
{
	Vector direction = GetThrowDirection(isLeft);
	this->body->AddForce(throwForce, direction);
}
