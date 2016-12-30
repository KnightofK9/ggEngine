#include "EnemyBase.h"
#include "Simon.h"
#include "CVDebugDefine.h"
#include "AnimationManager.h"
#include "CVSpriteAnimation.h"
#include "CVGame.h"
#include "EnemyGroup.h"
#include "TileBrick.h"
EnemyBase::EnemyBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image, frameWidth,frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->simon = this->cvGame->simon;
	this->simonDetectRange = 50.0;
	this->simonMinRespawnDistance = 50.0;

	this->tag = ObjectType_Enemy;
	cvGame->physics->AttachBodyTo(this);
	this->SetAnchor(0.5, 0);
	this->body->SetPhysicsMode(PhysicsMode_AABBSwept);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
	//this->body->immoveable = false;
	this->events->onCheckingCollide = [this](GameObject* go, ColliderArg e) {
		return OnCheckingCollide(e);
	};
	this->events->onOverlap = [this](GameObject* go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;

		switch (tag) {
		case ObjectType_LevelTwoBrick:
			OnBrickContact(dynamic_cast<TileBrick*>(otherObject), e);
			break;

		case ObjectType_Simon:
			OnSimonContact(e);
			break;
		}
	};
	this->events->onCollide = [this](GameObject* go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;

		switch (tag) {
		case ObjectType_LevelTwoBrick:
			OnBrickContact(dynamic_cast<TileBrick*>(otherObject), e);
			break;
		}
	};
	this->cvGame->eventManager->EnableEventUpdate(this, false);
	this->events->onUpdate = [this](GameObject*) {
		Update();
	};

	this->SetAlive(false);
	this->body->SetEnable(false);
}

EnemyBase::~EnemyBase()
{
}


bool EnemyBase::IsInRect(Rect r)
{
	Rect o = this->body->GetRect();
	Rect i;
	return Rect::intersect(i,o,r);
}

void EnemyBase::Death()
{
	this->cvGame->animationManager->AddEnemyDeathAnimation(this->position.x, this->position.y);
	Kill();
	GameObject::SetPosition(this->startPosition, true);
	auto enemyGroup = dynamic_cast<EnemyGroup*>(this->parentGroup);
	enemyGroup->AddEnemyToRetriveList(this);
}

void EnemyBase::OnSimonContact(ColliderArg e)
{
#ifdef DEBUG_SHOW_LOG_WHEN_ENEMY_CONTACT_SIMON
	g_debug.Log("Enemy contacted simon");
#endif //DEBUG_SHOW_LOG_WHEN_ENEMY_CONTACT_SIMON

#ifndef DEBUG_ENEMY_NOT_HURT_SIMON_WHEN_CONTACT
	//if (this->cvGame->simon->canContactWithEnemy) {
	//	this->cvGame->simon->Hurt(e.blockDirection.left);
	//	this->cvGame->simon->LoseHealth(damage);
	//}
#endif //DEBUG_ENEMY_NOT_HURT_SIMON_WHEN_CONTACT
}


bool EnemyBase::OnCheckingCollide(ColliderArg e)
{
	return false;
}

void EnemyBase::Active()
{
	this->body->velocity = Vector::Zero();
	this->PlayAnimation("default");
	this->SetAlive(true);
	this->body->SetEnable(true);
	this->currentHealth = maxHealth;
}
void EnemyBase::Update()
{
	if (allowToDetectSimon) {
		Vector simon = this->cvGame->simon->position;
		bool isInX = abs(simon.x - this->position.x) < this->simonDetectRange;
		bool isInY = abs(simon.y - this->position.y) < this->simonDetectRange;
		bool isInDetectXRange = this->position.y < simon.y && this->position.y + GetHeight() > simon.y;
		bool isInDetectYRange = this->position.x < simon.x && this->position.x + GetWidth() > simon.x;
		bool isSimonRight = simon.x > this->position.x;
		if ((detectX && detectY && isInX && isInY)		
			|| (detectX && !detectY && isInDetectXRange && isInX )
			|| (detectY && !detectX && isInDetectYRange && isInY)
			){
			OnSimonEnterRange(this->cvGame->simon, !isSimonRight);
		}
		else {
			OnSimonOutOfRange(this->cvGame->simon, !isSimonRight);
		}
	}
}
void EnemyBase::SetPosition(Vector position , bool isRefresh)
{
	GameObject::SetPosition(position, isRefresh);
	this->startPosition = position;
	//g_debug.Log("Setting start position for " + this->name + this->startPosition.ToString());
}
void EnemyBase::Kill()
{
	Active();
	GameObject::SetPosition(this->startPosition);
	GameObject::Kill();
}

double EnemyBase::GetDamage()
{
	return this->damage;
}
double EnemyBase::GetPoint()
{
	return this->point;
}
void EnemyBase::RunLeft()
{
}
void EnemyBase::RunRight()
{
}
void EnemyBase::OnSimonEnterRange(Simon * simon,bool isLeft)
{
	if (isLeft) {
		RunLeft();
	}
	else {
		RunRight();
	}
	//this->allowToDetectSimon = false;
}
void EnemyBase::OnSimonOutOfRange(Simon * simon, bool isLeft)
{
}
void EnemyBase::OnBrickContact(TileBrick *tileBrick, ColliderArg e)
{

}
int EnemyBase::LoseHealth(int health)
{
	if (!this->canContact)
		return 0;

	this->currentHealth -= health;
	if (this->currentHealth <= 0) {
		this->Death();
		return this->GetPoint();
	}

	this->canContact = false;
	this->cvGame->add->TimeOut(300, [this] {
		this->canContact = true;
	})->Start();
	return 0;
}
void EnemyBase::Destroy()
{
	CVSpriteAnimation::Destroy();
}
void EnemyBase::ChangeFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
	if (isLeft) {
		this->SetScale(1, 1);
	}
	else {
		this->SetScale(-1, 1);
	}
}
