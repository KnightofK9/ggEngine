#include "Simon.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "TextureConstant.h"
#include "ItemManager.h"
#include "WeaponManager.h"
#include "TileLadder.h"
Simon::Simon(CVGame *cvGame, SpriteInfo * image,InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CharacterBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->weaponManager = cvGame->weaponManager;

	this->tag = ObjectType_Simon;
	this->health = 16;
	this->maxHealth = 16;
	this->infoPanel = infoPanel;
	this->SetPosition(0, 0);
	Vector anchor(0.5, 20/25.0);
	this->SetAnchor(anchor.x, anchor.y);
	this->SetScale(1, 1);
	this->SetHealth(health);
	this->CreateAnimation("idle", 0, 0, true);
	this->CreateAnimation("move", 1, 2, true);
	this->CreateAnimation("kneel", 4, 4, true);
	this->CreateAnimation("climbDown", { 6,5,5 } ,false);
	this->CreateAnimation("climbDownIdle", 5, 5, true);
	this->CreateAnimation("climbUp", { 8,7,7 }, false);
	this->CreateAnimation("climbUpIdle", 7, 7, true);
	this->CreateAnimation("behind", 9, 9, true);
	this->CreateAnimation("hurt", 10, 10, true);
	this->CreateAnimation("death", 11, 11, true);
	this->PlayAnimation("climbUp");
	//Stand Attack
	this->CreateAnimation("standAttack", { 12,13,14,14 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	//// Kneel Attack
	this->CreateAnimation("kneelAttack", { 15,16,17,17 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	////Climb Down Attack
	this->CreateAnimation("climbDownAttack", { 18,19,20,20 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	////Climb Up Attack
	this->CreateAnimation("climbUpAttack", { 21,22,23,23 }, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});




	this->cvGame->physics->EnablePhysics(this);
	this->body->SetPhysicsMode(PhysicsMode_AABBSweptMix);
	this->body->CreateRectangleRigidBody(14, 25);
	this->body->syncBounds = false;
	this->body->rigidBody->SetAnchor(anchor.x, anchor.y - 0.1);
	this->body->allowGravity = true;
	this->body->allowWorldBounciness = false;
	this->body->allowWorldBlock = true;
	this->events->onCheckingCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LadderDownLeft:
			//this->ladderState = LadderDownLeft;
			return false;
		case ObjectType_LadderDownRight:
			//this->ladderState = LadderDownRight;
			return false;
		case ObjectType_LadderUpLeft:
		case ObjectType_LadderUpRight:
			this->isSteppingOnLadder = true;
			this->steppingTileLadder = dynamic_cast<TileLadder*>(otherObject);
			return true;
		case ObjectType_Static:
			return true;
		case ObjectType_LevelTwoBrick:
			return true;
		default:
			return false;
		}
		return false;

	};
	this->events->resetEvent = [=]() {
		this->tileLadder = nullptr;
		this->isSteppingOnLadder = false;
		this->steppingTileLadder = nullptr;
	};
	this->events->onCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LevelTwoBrick:
			if (e.blockDirection.down) {
				//this->ladderState = LadderNone;
				this->grounding = SimonGrounding_Brick;
			}
			break;
		case ObjectType_Candle:
			//g_debug.Log("Collided with candle");
			break;
		case ObjectType_LadderDownLeft:
		case ObjectType_LadderDownRight:
			break;
		case ObjectType_LadderUpLeft:
		case ObjectType_LadderUpRight:
			if (e.blockDirection.down)
				this->grounding = SimonGrounding_Brick;
			break;
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
	this->events->onOverlap = [this](GameObject *go, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;

		switch (type) {
		case ObjectType_LadderDownLeft:
		case ObjectType_LadderDownRight:
		case ObjectType_LadderUpLeft:
		case ObjectType_LadderUpRight:
			//g_debug.Log("Overlap with ladder!" + std::to_string(Helper::GetRamdomIntNumber()));
			tileLadder = dynamic_cast<TileLadder*>(e.colliderObject);
			break;
		}
	};
	this->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		if (e.blockDirection.down) {
			this->grounding = SimonGrounding_Brick;
		}
	};

	this->cvGame->eventManager->EnableKeyBoardInput(this);
	this->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		if (this->health <= 0)
			return;

		if (currentAutoLadderTweenAuto != nullptr) return;
		if (this->incompleteAnim != "") {
			this->PlayAnimation(incompleteAnim);
			return;
		}
		if (isClimbingLadder) {
			if (this->currentMoveToLadderTween != nullptr) {
				delete this->currentMoveToLadderTween;
				this->currentMoveToLadderTween = nullptr;
			}
			if (firstLadder == nullptr) firstLadder = tileLadder;
			this->body->allowGravity = false;
			bool isPressUp = e.isPress(controlKey[SimonControl_Up]);
			bool isPressDown = e.isPress(controlKey[SimonControl_Down]);
			if (tileLadder != nullptr  ) {
				switch (tileLadder->tag) {
				case ObjectType_LadderDownLeft:
				case ObjectType_LadderDownRight:
					if (isPressDown) OnLadderCompleted();
					break;
				}
				if(this->ladderState == SimonLadder_None) return;
			}

			switch (this->ladderState)
			{
				case SimonLadder_DownLeft:
				case SimonLadder_UpRight:
					if (isPressUp) MoveLadderUp(false);
					else if (isPressDown) MoveLadderDown(true);
					break;
				case SimonLadder_DownRight:
				case SimonLadder_UpLeft:
					if (isPressUp) MoveLadderUp(true);
					else if (isPressDown) MoveLadderDown(false);
					break;
				default:
					break;
			}

			//return;
		}
		else {
			if (this->isSteppingOnLadder) {
				this->tileLadder = steppingTileLadder;
				steppingTileLadder = nullptr;
				isSteppingOnLadder = false;
			}
			if (this->tileLadder != nullptr) {
				switch (this->tileLadder->tag)
				{
				case ObjectType_LadderDownLeft:
					
					if (e.isPress(controlKey[SimonControl_Up])) {
						this->ladderState = SimonLadder_DownLeft;
						this->StartClimbingLadder(false, true);
						return;
					}
					break;
				case ObjectType_LadderDownRight:
					
					if (e.isPress(controlKey[SimonControl_Up])) {
						this->ladderState = SimonLadder_DownRight;
						this->StartClimbingLadder(true, true);
						return;
					}
					break;
				case ObjectType_LadderUpLeft:
					
					/*this->StartClimbingLadder(false, false);
					return;*/
					if (e.isPress(controlKey[SimonControl_Down])) {
						this->ladderState = SimonLadder_UpLeft;
						this->StartClimbingLadderAuto(false, false);
						return;
					}
					break;
				case ObjectType_LadderUpRight:
					
					/*this->StartClimbingLadder(true, false);
					return;*/
					if (e.isPress(controlKey[SimonControl_Down])) {
						this->ladderState = SimonLadder_UpRight;
						this->StartClimbingLadderAuto(true, false);
						return;
					}
					if (currentAutoLadderTweenAuto !=  nullptr) return;
					break;
				default:
					break;
				}
				SetStateGoToLadder(false);

			}
			else {
				//this->ladderState == LadderNone;
			}
			
			
		}
		isSteppingOnLadder = false; 
		switch (this->grounding) {
			case SimonGrounding_Brick:
				this->body->allowGravity = true;
				if (CheckKeyValid(e) == false)
					this->Idle();
				else {
					CheckKeyPressNormal(e);
#ifdef _DEBUG
					CheckKeyWhenDebug(e);
#endif // _DEBUG

				}
				break;

			case SimonGrounding_Ladder:
				switch (this->ladderState) {
				case SimonLadder_DownLeft:
					CheckKeyPressLadderDownLeft(e);
					break;

				case SimonLadder_DownRight:
					CheckKeyPressLadderDownRight(e);
					break;

				case SimonLadder_UpLeft:
					CheckKeyPressLadderUpLeft(e);
					break;

				case SimonLadder_UpRight:
					CheckKeyPressLadderUpRight(e);
					break;

				//case SimonLadder_None:
				//	g_debug.Log("Ladder none");
				//	this->Idle();
				//	break;
				}
				break;

			case SimonGrounding_None:
				this->body->allowGravity = true;
				CheckKeyPressJumping(e);
				break;
			}
	};
	
	this->SetUpKeyControl();
	this->SetUpTestKeyControl();
	this->subWeapon = SimonSubWeaponType::SubWeapon_None;
	this->shot = 3;
	this->numberWeaponCanFire = this->shot;
	this->isReadyToFireWeapon = true;
	this->isAlive = true;
	this->score = 0;
	this->stagePoint = 1;
	this->heartPoint = 50;
	this->pPoint = 3;
}

Simon::~Simon()
{
	if (this->weaponWhip != nullptr) {
		delete this->weaponWhip;
	}
}

void Simon::SetHealth(int heath)
{
	this->health = heath;
	if (this->health < 0) this->health = 0;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
	if (this->health == 0) Death();
}

void Simon::Attack()
{
	if (!this->isReadyToFireWeapon || this->numberWeaponCanFire <= 0)
		return;

	this->isReadyToFireWeapon = false;
	this->weaponManager->AddWeapon(this, position.x, position.y, isLeft, this->parentGroup);
	this->numberWeaponCanFire--;


	// Set time to wait
	int timeToWaiting = CharacterConstant::SIMON_FIRE_LONG_TIME;
	if (this->numberWeaponCanFire > 0)
		timeToWaiting = CharacterConstant::SIMON_FIRE_SHORT_TIME;

	this->cvGame->add->TimeOut(timeToWaiting, [this] {
		this->isReadyToFireWeapon = true;
	})->Start();

	if (this->numberWeaponCanFire <= 0)
		this->numberWeaponCanFire = this->shot;
}

void Simon::AddWhip()
{
	this->weaponWhip = this->weaponManager->AddWeaponWhip(0, 8, isLeft, this->parentGroup);
	this->weaponWhip->SetAnchor(0.64, 0.5);
	this->weaponWhip->SetTransformBasedOn(this);
}

void Simon::Idle()
{
	this->PlayAnimation("idle");
	this->body->velocity.x = 0;
}

void Simon::MoveLeft()
{
	this->PlayAnimation("move");
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::MoveRight()
{
	this->PlayAnimation("move");
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::Jump()
{
	if (grounding == SimonGrounding_Brick)
	{
		this->PlayAnimation("kneel");
		this->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		grounding = SimonGrounding_None;
	}
}

void Simon::Kneel()
{
	this->PlayAnimation("kneel");
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
}

void Simon::ClimbUpLeft()
{
	this->PlayAnimation("climbUp");
	this->isClimbingUp = true;
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbUpRight()
{
	this->PlayAnimation("climbUp");
	this->isClimbingUp = true;
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownLeft()
{
	this->PlayAnimation("climbDown");
	this->isClimbingUp = false;
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownRight()
{
	this->PlayAnimation("climbDown");
	this->isClimbingUp = false;
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbIdle()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;

	if (this->isClimbingUp)
		PlayAnimation("climbUpIdle");
	else
		PlayAnimation("climbDownIdle");
}

void Simon::Hurt()
{
	this->PlayAnimation("hurt");
	this->Blind();
	//this->body->SetEnable(false);

	Vector direction(1, -3);
	if (isLeft)
		direction.x = -1;
	this->body->AddForce(hurtForce, direction);

	this->cvGame->add->TimeOut(2000, [this] {
		//this->body->SetEnable(true);
	})->Start();

}

void Simon::Death()
{
	this->PlayAnimation("death");
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	//this->cvGame->eventManager->DisableKeyBoardInput(this);
}

void Simon::StandAttack()
{
	this->body->velocity.x = 0;
	this->PlayAnimation("standAttack");
	this->incompleteAnim = "standAttack";
	//this->WhipAttack();
	this->weaponWhip->StandAttack(isLeft);
}

void Simon::KneelAttack()
{
	this->body->velocity.x = 0;
	this->PlayAnimation("kneelAttack");
	this->incompleteAnim = "kneelAttack";
	this->weaponWhip->KneelAttack(isLeft);
}

void Simon::ClimbAttack()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;

	if (this->isClimbingUp) {
		this->PlayAnimation("climbUpAttack");
		this->incompleteAnim = "climbUpAttack";
		this->weaponWhip->ClimbUpAttack(isLeft);
	}
	else {
		this->PlayAnimation("climbDownAttack");
		this->incompleteAnim = "climbDownAttack";
		this->weaponWhip->ClimbDownAttack(isLeft);
	}
}

void Simon::LoseHealth(int health)
{
	this->health -= health;
	if (this->health <= 0) {
		this->health = 0;
		this->Death();
	}
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
}

void Simon::GainHealth(int health)
{
	this->health += health;
	if (this->health > this->maxHealth) this->health = this->maxHealth;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
}

void Simon::IncreaseScore(int score)
{
	this->score += score;
	this->infoPanel->SetScore(this->score);
}

void Simon::IncreaseState()
{
	if(infoPanel!=nullptr) this->infoPanel->SetState(++this->stagePoint);
}

void Simon::IncreaseHeartPoint(int point)
{
	this->heartPoint += point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(heartPoint);
}

void Simon::DecreaseHeartPoint(int point)
{
	this->heartPoint = (heartPoint - point <= 0) ? 0 : heartPoint - point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(this->heartPoint);
}

void Simon::DescreasePPoint(int point)
{
	this->pPoint = (pPoint - point <= 0) ? 0 : pPoint - point;
	if (infoPanel != nullptr) this->infoPanel->SetLife(this->pPoint);
}

void Simon::SetSubWeapon(SimonSubWeaponType weaponType, SpriteInfo * image)
{
	this->subWeapon = weaponType;
	this->infoPanel->SetItemImage(image);
}



void Simon::SetShot(int shot, SpriteInfo * image)
{
	this->shot = shot;
	this->infoPanel->itemShot->SetImage(image);
}

void Simon::UpgradeWhip()
{
	this->weaponWhip->UpgradeWhip();

	this->Blind();
	// Will be changed to stopTime
	this->cvGame->eventManager->DisableKeyBoardInput(this);
	this->body->velocity.x = 0;
	this->Idle();
	this->cvGame->add->TimeOut(2000, [this] {
		this->cvGame->eventManager->EnableKeyBoardInput(this);
	})->Start();
}

void Simon::Blind()
{
	this->cvGame->add->Loop(100, 20, [this] {
		this->SetVisible(!this->IsVisible());
	})->Start();
}


void Simon::StartClimbingLadder(bool isLeft, bool isUp)
{
	SetStateGoToLadder(true);
	if (this->currentMoveToLadderTween == nullptr) {
		this->currentMoveToLadderTween = this->cvGame->add->MoveTo(
			this, 
			this->tileLadder->position+Vector(8,8),
			max(abs((this->tileLadder->position.x - this->position.x) / CharacterConstant::SIMON_MOVE_FORCE)*msPerFrame, abs((this->tileLadder->position.y - this->position.y) / CharacterConstant::SIMON_MOVE_FORCE)*msPerFrame),
			//10000,
			Easing::linearTween,
			false)
			->SetOnFinish([this]() {
			this->grounding = SimonGrounding_Ladder;
			this->isClimbingUp = true;
			this->isClimbingLadder = true;
		})->Start();
	}
	this->currentMoveToLadderTween->Update(this->msPerFrame);

	

}

void Simon::StartClimbingLadderAuto(bool isLeft, bool isUp)
{
	SetStateGoToLadder(true);
	if (this->currentAutoLadderTweenAuto == nullptr) {
		this->PlayAnimation("climbDown");
		this->currentAutoLadderTweenAuto = this->cvGame->add->MoveTo(
			this,
			this->tileLadder->position + Vector(8, 8),
			//max(abs((this->tileLadder->position.x - this->position.x) / CharacterConstant::SIMON_MOVE_FORCE)*msPerFrame, abs((this->tileLadder->position.y - this->position.y) / CharacterConstant::SIMON_MOVE_FORCE)*msPerFrame),
			this->msPerFrame*2,
			Easing::linearTween,
			true)
			->SetOnFinish([this]() {
			currentAutoLadderTweenAuto = nullptr;
			this->grounding = SimonGrounding_Ladder;
			this->isClimbingUp = false;
			this->isClimbingLadder = true;
		})->Start();
	}
}

void Simon::SetStateGoToLadder(bool active)
{
	if (active) {
		this->body->allowGravity = false;
		this->body->immoveable = true;
	}
	else {
		this->body->allowGravity = true;
		this->body->immoveable = false;
		if (this->currentMoveToLadderTween != nullptr) {
			delete this->currentMoveToLadderTween;
			this->currentMoveToLadderTween = nullptr;
		}
	}
}

void Simon::OnLadderCompleted()
{
	g_debug.Log("On ladder completed!");
	this->isClimbingLadder = false;
	this->ladderState = SimonLadder_None;
	firstLadder = nullptr;
	tileLadder = nullptr;
	this->body->allowGravity = true;
	this->body->immoveable = false;
}

void Simon::MoveLadderUp(bool isLeft,double force)
{
	if (this->currentLadderTween == nullptr) {
		Vector distance;
		if (isLeft) {
			distance = Vector(-force, -force);
		}
		else {
			distance = Vector(force, -force);
		}
		ChangeFacingDirection(isLeft);
		this->PlayAnimation("climbUp");
		bool isSteppingOnLadder2 = false;
		if (this->tileLadder != nullptr) {
			switch (this->tileLadder->tag) {
			case ObjectType_LadderUpLeft:
			case ObjectType_LadderUpRight:
				isSteppingOnLadder2 = true;
			}
		}
		this->currentLadderTween = this->cvGame->add->MoveBy(this, distance, this->msPerFrame * 2)->SetOnFinish([=]() {
			if (isSteppingOnLadder2) {
				OnLadderCompleted();
			}
			this->currentLadderTween = nullptr;
		})->Start();
	}
}

void Simon::MoveLadderDown(bool isLeft, double force)
{
	if (this->currentLadderTween == nullptr) {
		Vector distance;
		if (isLeft) {
			distance = Vector(-force, force);
		}
		else {
			distance = Vector(force, force);
		}
		ChangeFacingDirection(isLeft);
		this->PlayAnimation("climbDown");
		this->currentLadderTween = this->cvGame->add->MoveBy(this, distance, this->msPerFrame * 3)->SetOnFinish([this]() {
			this->currentLadderTween = nullptr;
		})->Start();
	}
}





void Simon::SetUpKeyControl()
{
	controlKey[SimonControl_Left] = DIK_LEFT;
	controlKey[SimonControl_Right] = DIK_RIGHT;
	controlKey[SimonControl_Up] = DIK_UP;
	controlKey[SimonControl_Down] = DIK_DOWN;
	controlKey[SimonControl_TurboA] = DIK_C;
	controlKey[SimonControl_TurboB] = DIK_V;
	controlKey[SimonControl_A] = DIK_Z;
	controlKey[SimonControl_B] = DIK_X;
}

bool Simon::CheckKeyValid(KeyBoardEventArg e)
{
	int n = sizeof(controlKey) / sizeof(*controlKey);
	for (int i = 0; i < n; i++) {
		if (e.isPress(controlKey[i]))
			return true;
	}
	return false;
}

void Simon::SetUpTestKeyControl()
{
	controlKey[SimonControl_Num1] = DIK_1;
	controlKey[SimonControl_Num2] = DIK_2;
	controlKey[SimonControl_Num3] = DIK_3;
	controlKey[SimonControl_Num4] = DIK_4;
	controlKey[SimonControl_Num5] = DIK_5;
	controlKey[SimonControl_Num6] = DIK_6;
	controlKey[SimonControl_Num7] = DIK_7;
	controlKey[SimonControl_Num8] = DIK_8;
	controlKey[SimonControl_Num9] = DIK_9;
	controlKey[SimonControl_Num0] = DIK_0;
}

void Simon::CheckKeyWhenDebug(KeyBoardEventArg e)
{
	SimonSubWeaponType weaponType = SimonSubWeaponType::SubWeapon_None;
	SpriteInfo *inf = nullptr;


	if (e.isPress(controlKey[SimonControl_Num1])) {
		this->shot = 1;
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num2])) {
		this->shot = 2;
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num3])) {
		this->shot = 3;
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num4])) {
		weaponType = SimonSubWeaponType::SubWeapon_HolyWater;
		inf = this->cvGame->cache->GetSpriteInfo(TextureConstant::HOLY_WATER_TEXTURE);
	}
	if (e.isPress(controlKey[SimonControl_Num5])) {
		weaponType = SimonSubWeaponType::SubWeapon_StopWatch;
		inf = this->cvGame->cache->GetSpriteInfo(TextureConstant::STOPWATCH_TEXTURE);
	}
	if (e.isPress(controlKey[SimonControl_Num6])) {
		weaponType = SimonSubWeaponType::SubWeapon_Axe;
		inf = this->cvGame->cache->GetSpriteInfo(TextureConstant::AXE_TEXTURE);
	}
	if (e.isPress(controlKey[SimonControl_Num7])) {
		weaponType = SimonSubWeaponType::SubWeapon_Boomerang;
		inf = this->cvGame->cache->GetSpriteInfo(TextureConstant::BOOMERANG_TEXTURE);
	}
	if (e.isPress(controlKey[SimonControl_Num8])) {
		weaponType = SimonSubWeaponType::SubWeapon_Dagger;
		inf = this->cvGame->cache->GetSpriteInfo(TextureConstant::DAGGER_TEXTURE);
	}
	if (e.isPress(controlKey[SimonControl_Num9])) {
		this->GainHealth(1);
		return;
	}
	if (e.isPress(controlKey[SimonControl_Num0])) {
		this->LoseHealth(1);
		return;
	}
	if (weaponType != SubWeapon_None && inf != NULL) {
		this->SetSubWeapon(weaponType, inf);
		this->Attack();
	}
}

void Simon::CheckKeyPressNormal(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->MoveLeft();
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->MoveRight();
	}

	if (e.isPress(controlKey[SimonControl_A])) {
		this->Jump();
		this->grounding = SimonGrounding_None;
	}

	if (e.isPress(controlKey[SimonControl_B])
		&& e.isPress(controlKey[SimonControl_Down])) {
		this->KneelAttack();
	} else {
		if (e.isPress(controlKey[SimonControl_Down]))
			this->Kneel();
		if (e.isPress(controlKey[SimonControl_B]))
			this->StandAttack();
	}
	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
	}
}

void Simon::CheckKeyPressJumping(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_B]))
		this->StandAttack();
	if (e.isPress(controlKey[SimonControl_TurboB]))
		this->Attack();
}

void Simon::CheckKeyPressLadderDownLeft(KeyBoardEventArg e)
{
	//if (e.isPress(controlKey[SimonControl_Left])) {
	//	this->ClimbDownLeft();
	//	return;
	//}

	//if (e.isPress(controlKey[SimonControl_Right])) {
	//	this->ClimbUpRight();
	//	return;
	//}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		if (isClimbingUp) {
			this->PlayAnimation("climbUpAttack");
		}
		else {
			this->PlayAnimation("climbDownAttack");
		}
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}

	this->ClimbIdle();
}

void Simon::CheckKeyPressLadderDownRight(KeyBoardEventArg e) {
	//if (e.isPress(controlKey[SimonControl_Left])) {
	//	this->ClimbUpLeft();
	//	return;
	//}

	//if (e.isPress(controlKey[SimonControl_Right])) {
	//	this->ClimbDownRight();
	//	return;
	//}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		if (isClimbingUp) {
			this->PlayAnimation("climbUpAttack");
		} else {
			this->PlayAnimation("climbDownAttack");
		}
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}

	this->ClimbIdle();
}

void Simon::CheckKeyPressLadderUpLeft(KeyBoardEventArg e) {
	//if (e.isPress(controlKey[SimonControl_Left])) {
	//	this->ClimbUpLeft();
	//	return;
	//}

	//if (e.isPress(controlKey[SimonControl_Right])) {
	//	this->ClimbDownRight();
	//	return;
	//}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		if (isClimbingUp) {
			this->PlayAnimation("climbUpAttack");
		}
		else {
			this->PlayAnimation("climbDownAttack");
		}
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}

	this->ClimbIdle();
}

void Simon::CheckKeyPressLadderUpRight(KeyBoardEventArg e) {


	//if (e.isPress(controlKey[SimonControl_Left])) {
	//	this->ClimbDownLeft();
	//	return;
	//}

	//if (e.isPress(controlKey[SimonControl_Right])) {
	//	this->ClimbUpRight();
	//	return;
	//}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		if (isClimbingUp) {
			this->PlayAnimation("climbUpAttack");
		}
		else {
			this->PlayAnimation("climbDownAttack");
		}
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}

	this->ClimbIdle();
}



