#pragma once
#include "CVSpriteAnimation.h"
#include "TypeEnum.h"
class EnemyBase;
class CVGame;
class EnemySkillBase : public CVSpriteAnimation {
public:
	EnemySkillBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemySkillBase();

	void Active();
	void SetParentObject(EnemyBase *enemyBase);
	virtual void Fire(bool isLeft, Vector position);
	virtual void ChangeFacingDirection(bool isLeft);
protected:
	template <class T>
	inline T* AddSkill(Vector position);
	virtual void OnSimonContact(ColliderArg e);
	virtual bool OnCheckingCollide(ColliderArg e);
	EnemyBase *enemyBase;
	bool isLeft;
	double fireSpeed = 0.25;
};

template<class T>
inline T * EnemySkillBase::AddSkill(Vector position)
{
	T* go = new T(this->cvGame, this->image);
	this->cvGame->simon->currentMap->projectileGroup->AddDrawObjectToList(go);
	go->SetPosition(position);
	go->UpdateWorldPosition();
	go->body->PreUpdate();
	return go;
}
