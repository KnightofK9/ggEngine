#include "Simon.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "ItemManager.h"
#include "WeaponManager.h"
Simon::Simon(CVGame *cvGame, SpriteInfo * image,InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CharacterBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->weaponManager = cvGame->weaponManager;

	this->tag = ObjectType_Simon;
	this->health = 16;
	this->maxHealth = 16;
	this->infoPanel = infoPanel;
	this->SetPosition(0, 0);
	this->SetAnchor(0.5, 0.5);
	this->SetScale(1, 1);
	this->SetHealth(health);
	this->CreateAnimation("idle", 0, 0, true);
	this->CreateAnimation("move", 1, 3, true);
	this->CreateAnimation("kneel", 4, 4, true);
	this->CreateAnimation("climbDown", 5, 6, true);
	this->CreateAnimation("climbUp", 7, 8, true);
	this->CreateAnimation("behind", 9, 9, true);
	this->CreateAnimation("hurt", 10, 10, true);
	this->CreateAnimation("death", 11, 11, true);

	//Create "after ... attack" to double the frame which whip is shown longest
	//Stand Attack
	this->CreateAnimation("standAttack", 12, 14, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "afterStandAttack";
	});
	this->CreateAnimation("afterStandAttack", 14, 14, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	// Kneel Attack
	this->CreateAnimation("kneelAttack", 15, 17, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "afterKneelAttack";
	});
	this->CreateAnimation("afterKneelAttack", 17, 17, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	//Climb Down Attack
	this->CreateAnimation("climbDownAttack", 18, 20, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "afterClimbDownAttack";
	});
	this->CreateAnimation("afterClimbDownAttack", 20, 20, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});

	//Climb Up Attack
	this->CreateAnimation("climbUpAttack", 21, 23, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "afterClimbUpAttack";
	});
	this->CreateAnimation("afterClimbUpAttack", 23, 23, false)->SetOnCompleted([this](Animator*) {
		this->incompleteAnim = "";
	});




	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(20, 30);
	this->body->syncBounds = false;
	this->body->rigidBody->SetAnchor(0.5, 0.32);
	this->body->allowGravity = true;
	this->body->allowWorldBounciness = false;
	this->body->allowWorldBlock = true;
	this->events->onCheckingCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LadderDownLeft:
				this->ladder = LadderDownLeft;
			break;
		case ObjectType_LadderDownRight:
		case ObjectType_LadderUpLeft:
		case ObjectType_LadderUpRight:
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
	this->events->onCollide = [this](GameObject *object, ColliderArg e) {
		GameObject *otherObject = e.colliderObject;
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_LevelTwoBrick:
			if (e.blockDirection.down) {
				this->ladder = LadderNone;
				this->grounding = GroundingBrick;
			}
			break;
		case ObjectType_Candle:
			//g_debug.Log("Collided with candle");
			break;
		/*case ObjectType_LadderDownLeft:
			this->grounding = GroundingLadder_DownLeft;
			break;
		case ObjectType_LadderDownRight:
			this->grounding = GroundingLadder;
			break;
		case ObjectType_LadderUpLeft:
			this->grounding = GroundingLadder;
			break;
		case ObjectType_LadderUpRight:
			this->grounding = GroundingLadder;
			break;*/
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
		if (e.blockDirection.down) {
			this->grounding = GroundingBrick;
		}
	};

	this->cvGame->eventManager->EnableKeyBoardInput(this);
	this->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		/*if (this->GetHealth() <= 0) {
			this->Death();
			return;`
		}*/

		if (this->incompleteAnim != "") {
			this->PlayAnimation(incompleteAnim);
			return;
		}
		if (this->ladder == LadderDownLeft && e.isPress(controlKey[SimonControl_Up])){
			this->grounding = GroundingLadder;
		}


		if (CheckKeyValid(e) == false)
			this->Idle();
		else {
			switch (this->grounding) {
			case GroundingBrick:
				this->body->allowGravity = true;
				SetKeyPressNormal(e);
				break;

			case GroundingLadder:
				this->body->allowGravity = false;
				switch (this->ladder) {
				case LadderDownLeft:
					SetKeyPressLadderDownLeft(e);
					break;

				case LadderDownRight:
					SetKeyPressLadderDownRight(e);
					break;

				case LadderUpLeft:
					SetKeyPressLadderUpLeft(e);
					break;

				case LadderUpRight:
					this->body->allowGravity = false;
					SetKeyPressLadderUpRight(e);
					break;
				}
			case GroundingNone:
				break;
			}
		}
	};
	
	this->SetUpKeyControl();
	this->shot = 1;
	this->score = 0;
	this->stagePoint = 1;
	this->heartPoint = 5;
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
	this->weaponManager->AddWeaponBoomerang(position.x, position.y, isLeft, this->parentGroup);
}

void Simon::WhipAttack()
{
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
	if (grounding == GroundingBrick)
	{
		this->PlayAnimation("kneel");
		this->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		//this->weaponWhip->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		grounding = GroundingNone;
	}
}

void Simon::Kneel()
{
	this->PlayAnimation("kneel");
	this->body->velocity.x = 0;
}

void Simon::ClimbUpLeft()
{
	this->PlayAnimation("climbUp");
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbUpRight()
{
	this->PlayAnimation("climbUp");
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = -CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownLeft()
{
	this->PlayAnimation("climbDown");
	ChangeFacingDirection(true);
	this->body->velocity.x = -CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
}

void Simon::ClimbDownRight()
{
	this->PlayAnimation("climbDown");
	ChangeFacingDirection(false);
	this->body->velocity.x = CharacterConstant::SIMON_CLIMB_FORCE;
	this->body->velocity.y = CharacterConstant::SIMON_CLIMB_FORCE;
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

void Simon::ClimbDownAttack()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	this->PlayAnimation("climbDownAttack");
	this->incompleteAnim = "climbDownAttack";
	this->weaponWhip->ClimbDownAttack(isLeft);
}

void Simon::ClimbUpAttack()
{
	this->body->velocity.x = 0;
	this->body->velocity.y = 0;
	this->PlayAnimation("climbUpAttack");
	this->incompleteAnim = "climbUpAttack";
	this->weaponWhip->ClimbUpAttack(isLeft);
}

void Simon::ClimbAttack()
{
	if (this->isClimbingUp)
		this->ClimbUpAttack();
	else
		this->ClimbDownAttack();
}

void Simon::LoseHealth(int health)
{
	this->health -= health;
	if (this->health < 0) this->health = 0;
	if (infoPanel != nullptr) {
		infoPanel->SetPlayerHealth(this->health);
	}
	if (this->health == 0) Death();
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

void Simon::SetKeyPressNormal(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->MoveLeft();
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->MoveRight();
	}

	if (e.isPress(controlKey[SimonControl_B])
		&& e.isPress(controlKey[SimonControl_Down])) {
		this->KneelAttack();
	}
	else {
		if (e.isPress(controlKey[SimonControl_Down]))
			this->Kneel();
		if (e.isPress(controlKey[SimonControl_B]))
			this->StandAttack();
	}
	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
	}

	if (e.isPress(controlKey[SimonControl_A])) {
		this->Jump();
		this->grounding = GroundingNone;
	}
}

void Simon::SetKeyPressLadderDownLeft(KeyBoardEventArg e)
{
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}
}

void Simon::SetKeyPressLadderDownRight(KeyBoardEventArg e) {
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->ClimbUpLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}
}

void Simon::SetKeyPressLadderUpLeft(KeyBoardEventArg e) {
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->ClimbUpLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}
}

void Simon::SetKeyPressLadderUpRight(KeyBoardEventArg e) {
	if (e.isPress(controlKey[SimonControl_Left])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Right])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Down])) {
		this->ClimbDownLeft();
		return;
	}

	if (e.isPress(controlKey[SimonControl_Up])) {
		this->ClimbUpRight();
		return;
	}

	if (e.isPress(controlKey[SimonControl_TurboB])) {
		this->Attack();
		return;
	}

	if (e.isPress(controlKey[SimonControl_B])) {
		this->ClimbAttack();
		return;
	}
}



