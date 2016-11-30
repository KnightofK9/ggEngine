#include "WeaponBase.h"
#include "CVGame.h"
#include "EnemyBase.h"
WeaponBase::WeaponBase(CVGame * cvGame, SpriteInfo * image) : CVSprite(cvGame->GetDrawManager(),image)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->body->allowGravity = true;


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
	this->events->onOutOfCamera = [this](GameObject *go, EventArg e) {
		OnOutOfCamera(e);
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
}

void WeaponBase::OnOutOfCamera(EventArg e)
{
}



void WeaponBase::OnStaticContact(GameObject * staticObject, ColliderArg e)
{
}

void WeaponBase::Active()
{
}
