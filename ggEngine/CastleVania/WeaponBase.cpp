#include "WeaponBase.h"
#include "CVGame.h"
#include "EnemyBase.h"
WeaponBase::WeaponBase(CVGame * cvGame, SpriteInfo * image) : CVSprite(cvGame->GetDrawManager(),image)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->body->allowGravity = true;
	this->body->syncBounds = false;

	this->tag = ObjectType_Weapon;
	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		switch (go->tag) {
		case ObjectType_Enemy:
			{
				EnemyBase *enemy = dynamic_cast<EnemyBase*>(go);
				if (enemy != nullptr) {
					OnEnemyContact(enemy, e);
					return;
				}
			}
			break;
		case ObjectType_Static:
			OnStaticContact(go,e);
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
}

void WeaponBase::FireWeapon(bool isLeft)
{
}

void WeaponBase::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
	Destroy();
}

void WeaponBase::OnOutOfCamera(EventArg e)
{
	g_debug.Log("Out of camera!");
	Destroy();
}



void WeaponBase::OnStaticContact(GameObject * staticObject, ColliderArg e)
{
	Destroy();
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

Vector WeaponBase::GetThrowDirection(bool isLeft)
{
	Vector direction(-1, -1);
	if (!isLeft) {
		direction.x = 1;
	}
	return direction;
}

void WeaponBase::FireHorizontal(bool isLeft)
{
	if (isLeft) {
		this->SetScale(-1, 1);
	}
	Vector direction = GetHorizontalDirection(isLeft);
	this->body->AddForce(this->throwForce, direction);
}

void WeaponBase::FireAsThrow(bool isLeft)
{
	Vector direction = GetThrowDirection(isLeft);
	this->body->AddForce(this->throwForce, direction);
}
