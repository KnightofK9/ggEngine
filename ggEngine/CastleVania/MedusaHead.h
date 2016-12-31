#pragma once
#include "TweenEnemyBase.h"
class MedusaHead : public TweenEnemyBase {
public:
	MedusaHead(CVGame* cvGame, SpriteInfo *spriteInfo);
	virtual ~MedusaHead();

	void RunLeft() override;
	void RunRight() override;
	void Update() override;


	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	void Active() override;
	void Fire(bool isLeft, Vector firePosition);
	void Kill() override;
	void SetBullet(bool isBullet);
	bool IsBullet();
private:
	bool isBullet;
	Timer shootTimer;
	unsigned int fireTimer;
	//const int damage = 2;
	//const int health = 1;
	//const int point = 300;
};