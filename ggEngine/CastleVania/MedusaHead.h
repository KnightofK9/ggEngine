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
private:
	//const int damage = 2;
	//const int health = 1;
	//const int point = 300;
};