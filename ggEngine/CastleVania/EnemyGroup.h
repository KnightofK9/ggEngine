#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class EnemyBase;
class Simon;
class EnemyGroup : public CameraActiveGroup {
public :
	EnemyGroup(CVGame *cvGame);
	virtual ~EnemyGroup();

	virtual void Update() override;

	void AddEnemyToRetriveList(EnemyBase * enemy);
	void RemoveEnemyFromRetriveList(EnemyBase *enemy);
	void ResetRetriveList();

	void LoadSimon(Simon *simon);
protected:
	void UpdateRetriveEnemy();
	std::list<EnemyBase*> retriveEnemyList;
	Simon* simon = nullptr;
};