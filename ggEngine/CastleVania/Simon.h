#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
#include "CharacterConstant.h"
#include "InfoPanel.h"
using namespace ggEngine;
class CVGame;
class ItemBase;
class WeaponManager;
class TileLadder;
class WeaponWhip;

enum SimonControl {
	SimonControl_Left = 0, SimonControl_Right, SimonControl_Up, SimonControl_Down,
	SimonControl_A, SimonControl_B, SimonControl_TurboA, SimonControl_TurboB,
	SimonControl_Num1,
	SimonControl_Num2,
	SimonControl_Num3,
	SimonControl_Num4,
	SimonControl_Num5,
	SimonControl_Num6,
	SimonControl_Num7,
	SimonControl_Num8,
	SimonControl_Num9,
	SimonControl_Num0
};
enum SimonGroundingType {SimonGrounding_Brick, SimonGrounding_Ladder, SimonGrounding_None};
enum SimonLadderType { SimonLadder_DownLeft, SimonLadder_DownRight, SimonLadder_UpLeft, SimonLadder_UpRight, SimonLadder_None};
enum SimonSubWeaponType { SubWeapon_HolyWater, SubWeapon_Dagger, SubWeapon_Boomerang, SubWeapon_StopWatch, SubWeapon_Axe, SubWeapon_None };

class Simon :public CharacterBase {
public:
	Simon(CVGame *cvGame, SpriteInfo *image, InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~Simon();
	void SetHealth(int heath);
	int GetHealth() { return this->health; }
	
	void SetMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	int GetMaxHealth() { return this->maxHealth; }
	int GetHeartPoint() { return this->heartPoint; }

	void Attack() override;
	void Update();
	void AddWhip();
	void SetGroupToCheckCollision(Group *checkingCollisionGroup) { this->checkingCollisionGroup = checkingCollisionGroup; }
	Group* GetGroupToCheckCollision() { return this->checkingCollisionGroup; }
	void Idle();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Kneel();
	void ClimbUpLeft();
	void ClimbUpRight();
	void ClimbDownLeft();
	void ClimbDownRight();
	void ClimbIdle();
	void Hurt();
	void Death();
	void StandAttack();
	void KneelAttack();
	void ClimbAttack();

	void LoseHealth(int health);
	void GainHealth(int health);
	void IncreaseScore(int score);
	void IncreaseState();
	void IncreaseHeartPoint(int point);
	void DecreaseHeartPoint(int point);
	void DescreasePPoint(int point);
	void SetSubWeapon(SimonSubWeaponType weaponType, SpriteInfo *image);
	void SetShot(int shot, SpriteInfo *image);
	void UpgradeWhip();

	void Blind();
	SimonSubWeaponType subWeapon;
	WeaponWhip *weaponWhip = nullptr;
	//void ThrowWeapon();

	void *HealthDown(int health) { this->health -= health; }

	InfoPanel *infoPanel = nullptr;
private:
	void StartClimbingLadder(bool isLeft, bool isUp);
	void StartClimbingLadderAuto(bool isLeft, bool isUp);
	void SetStateGoToLadder(bool active);
	Group* checkingCollisionGroup = nullptr;
	void OnLadderCompleted();
	TileLadder *tileLadder = nullptr;
	TileLadder *firstLadder = nullptr;
	int health;
	int maxHealth;
	const double ladderMoveDistance = 16;
	void MoveLadderUp(bool isLeft, double force = 16);
	void MoveLadderDown(bool isLeft, double force = 16);
	TweenBase* currentLadderTween = nullptr;
	TweenBase* currentAutoLadderTweenAuto = nullptr;
	TweenBase* currentMoveToLadderTween = nullptr;
	int score;
	bool isClimbingLadder = false;
	int stagePoint;
	bool isSteppingOnLadder = false;
	TileLadder *steppingTileLadder = nullptr;
	
	
	int heartPoint;
	int pPoint;
	int shot;
	int numberWeaponCanFire;
	bool isReadyToFireWeapon;
	bool isAlive;


	SimonGroundingType grounding = SimonGrounding_Brick;	//for jump or for fall down or for hurt
	SimonLadderType ladderState = SimonLadder_None;

	bool isClimbingUp = false;
	double hurtForce = 3;

	string incompleteAnim = "";
	WeaponManager *weaponManager = nullptr;
	
	DWORD controlKey[18];
	void SetUpKeyControl();
	bool CheckKeyValid(KeyBoardEventArg e);
	void SetUpTestKeyControl();
	void CheckKeyWhenDebug(KeyBoardEventArg e);

	void CheckKeyPressNormal(KeyBoardEventArg e);
	void CheckKeyPressJumping(KeyBoardEventArg e);
	void CheckKeyPressLadderDownLeft(KeyBoardEventArg e);
	void CheckKeyPressLadderDownRight(KeyBoardEventArg e);
	void CheckKeyPressLadderUpLeft(KeyBoardEventArg e);
	void CheckKeyPressLadderUpRight(KeyBoardEventArg e);

};