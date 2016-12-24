#pragma once
#include "CVSpriteAnimation.h"
class EnemyBase;
class EnemySkillBase : public CVSpriteAnimation {
public:
	EnemySkillBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemySkillBase();

	void Active();
	void SetParentObject(EnemyBase *enemyBase);
	virtual void Fire(bool isLeft, Vector position) = 0;
	template <class T>
	inline T* AddSkill(Vector position);
protected:
	virtual void OnSimonContact(ColliderArg e);
	virtual bool OnCheckingCollide(ColliderArg e);
	EnemyBase *enemyBase;
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