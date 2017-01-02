#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
class TileBrick;
using namespace ggEngine;
class Simon;
class EnemyBase : public CVSpriteAnimation {
public:
	EnemyBase(CVGame *cvGame, SpriteInfo *image,int frameWidth,int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemyBase();

	virtual void Active();
	virtual void Update();
	virtual int LoseHealth(int health);
	virtual void Destroy();

	double GetDamage();
	double GetPoint();
	virtual void SetPosition(Vector position , bool isRefresh = false) override;
	void Kill() override;

	bool canContact = true;
	bool IsInRect(Rect r);
	double simonMinRespawnDistance;
	int GetHealth();
protected:
	virtual void Death();
	Vector startPosition;
	virtual void OnSimonContact( ColliderArg e);
	virtual bool OnCheckingCollide(ColliderArg e);
	virtual void RunLeft();
	virtual void RunRight();
	virtual void OnSimonEnterRange(Simon* simon, bool isLeft);
	virtual void OnSimonOutOfRange(Simon* simon, bool isLeft);
	virtual void OnBrickContact(TileBrick *tileBrick, ColliderArg e);

	bool isLeft;
	void ChangeFacingDirection(bool isLeft);
	double health = 0.0f;
	double maxHealth;
	double currentHealth;
	double simonDetectRange;
	bool allowToDetectSimon = false;
	bool detectX = true;
	bool detectY = true;


	int point;
	int damage = 0;
	Simon* simon;
};