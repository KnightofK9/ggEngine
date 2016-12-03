#include "Simon.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "ItemManager.h"
#include "WeaponManager.h"
Simon::Simon(CVGame *cvGame, SpriteInfo * image,InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) : CharacterBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->weaponManager = cvGame->weaponManager;


	this->tag = ObjectType_Simon;
	this->health = 16;
	this->maxHealth = 16;
	this->isGrounding = true;
	this->infoPanel = infoPanel;
	this->SetPosition(0, 0);
	this->SetAnchor(0.5, 0.5);
	this->SetScale(1, 1);
	this->SetHealth(health);
	this->CreateAnimation("idle", 0, 0, true);
	this->CreateAnimation("move", 0, 3, true);
	this->CreateAnimation("kneel", 4, 4, true);
	this->CreateAnimation("climbUp", 5, 6, true);
	this->CreateAnimation("climbDown", 7, 8, true);
	this->CreateAnimation("behind", 9, 9, true);
	this->CreateAnimation("hurt", 10, 10, true);
	this->CreateAnimation("death", 11, 11, true);
	this->CreateAnimation("standAttack", 12, 14, true);
	this->CreateAnimation("kneelAttack", 15, 17, true);
	this->CreateAnimation("climbDownAttack", 18, 20, true);
	this->CreateAnimation("climbUpAttack", 21, 23, true);

	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(20, GetHeight());
	this->body->syncBounds = false;
	this->body->rigidBody->SetAnchor(0.5, 0.5);
	this->body->allowGravity = true;
	this->body->allowWorldBounciness = false;
	this->body->allowWorldBlock = true;
	this->events->onCheckingCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_Static:
			
			return true;
		default:
			return false;
		}
		return false;

	};
	this->events->onCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_Static:
		case ObjectType_Item:
			if (otherObject->events->onCollide != nullptr) {
				ColliderArg	o = Physics::CreateOppositeColliderArg(e, object);
				otherObject->events->onCollide(otherObject, o);
			}
			break;
		default:
			break;
		}

	};
	this->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		//Simon *this = dynamic_cast<Simon*>(go);
		this->isGrounding = true;
	};

	this->cvGame->eventManager->EnableKeyBoardInput(this);
	this->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		double time = this->cvGame->logicTimer.getDeltaTime();
		//double force = CharacterConstant::SIMON_MOVE_FORCE; //* time;
		//double currentJumpForce = CharacterConstant::SIMON_JUMP_FORCE;// *time;																	  //Move right

		this->Idle();

		if (this->GetHealth() <= 0) {
			this->Death();
			return;
		}

		if (this->isGrounding == false) {
			this->Kneel();
		}

		if (e.isPress(DIK_LEFT)) {
			this->MoveLeft();
		}
		if (e.isPress(DIK_RIGHT)) {
			this->MoveRight();
		}

		if (e.isPress(DIK_SPACE) && this->isGrounding == true) {
			this->cvGame->cvAdd->TimeOut(500, [this] {
				this->Idle();
			});
			this->Jump();
			this->isGrounding = false;
		}

		if (e.isPress(DIK_E) && e.isPress(DIK_DOWN)) {
			this->KneelAttack();
		}
		else {
			if (e.isPress(DIK_DOWN))
				this->Kneel();
			if (e.isPress(DIK_E))
				this->StandAttack();
		}
		if (e.isPress(DIK_Q)) {
			Attack();
		}
	};

	shot = 1;
	score = 0;
	stagePoint = 1;
	heartPoint = 5;
	pPoint = 3;
}

Simon::~Simon()
{
}

void Simon::SetHealth(int heath)
{
	this->health = heath;
	if (this->health < 0) this->health = 0;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	infoPanel->SetPlayerHealth(this->health);
	if (this->health == 0) Death();
}

void Simon::Attack()
{
	auto *weapon = this->weaponManager->AddWeaponBoomerang(this->position.x, this->position.y, isLeft, this->parentObject);
	if (this->heartPoint - weapon->heartConsumtion >= 0)
	{
		this->DecreaseHeartPoint(weapon->heartConsumtion);
		weapon->Active();
		weapon->FireWeapon(this->isLeft);
	}
	else
		weapon->Destroy();
}

void Simon::Idle()
{
	this->PlayAnimation("idle");
	this->body->velocity.x = 0;
}

void Simon::MoveLeft()
{
	this->PlayAnimation("move");
	/*this->SetScale(1, 1);*/
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::MoveRight()
{
	this->PlayAnimation("move");
	//this->SetScale(-1, 1);
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::Jump()
{
	if (isGrounding)
	{
		this->PlayAnimation("kneel");
		this->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		isGrounding = false;
	}
}

void Simon::Kneel()
{
	this->PlayAnimation("kneel");
	this->body->velocity.x = 0;
}

void Simon::ClimbUp()
{
	this->PlayAnimation("climbUp");
}

void Simon::ClimbDown()
{
	this->PlayAnimation("climbDown");
}

void Simon::Hurt()
{
	this->PlayAnimation("hurt");
}

void Simon::Death()
{
	this->PlayAnimation("death");
	this->body->velocity.x = 0;
}

void Simon::StandAttack()
{
	this->PlayAnimation("standAttack");
	this->body->velocity.x = 0;
}

void Simon::KneelAttack()
{
	this->PlayAnimation("kneelAttack");
	this->body->velocity.x = 0;
}

void Simon::ClimbDownAttack()
{
	this->PlayAnimation("climbDownAttack");
}

void Simon::ClimbUpAttack()
{
	this->PlayAnimation("climbUpAttack");
}

void Simon::LoseHealth(int health)
{
	this->health -= health;
	if (this->health < 0) this->health = 0;
	infoPanel->SetPlayerHealth(this->health);
	if (this->health == 0) Death();
}

void Simon::GainHealth(int health)
{
	this->health += health;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	infoPanel->SetPlayerHealth(this->health);
}

void Simon::IncreaseScore(int score)
{
	this->score += score;
	this->infoPanel->SetScore(this->score);
}

void Simon::IncreaseState()
{
	this->infoPanel->SetState(++this->stagePoint);
}

void Simon::IncreaseHeartPoint(int point)
{
	this->heartPoint += point;
	this->infoPanel->SetLife(heartPoint);
}

void Simon::DecreaseHeartPoint(int point)
{
	this->heartPoint = (heartPoint - point <= 0) ? 0 : heartPoint - point;
	this->infoPanel->SetLife(this->heartPoint);
}

void Simon::DescreasePPoint(int point)
{
	this->pPoint = (pPoint - point <= 0) ? 0 : pPoint - point;
	this->infoPanel->SetLife(this->pPoint);
}



void Simon::SetShot(int shot, SpriteInfo * image)
{
	this->shot = shot;
	this->infoPanel->itemShot->SetImage(image);
}
