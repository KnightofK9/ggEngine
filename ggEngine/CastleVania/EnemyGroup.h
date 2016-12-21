#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class EnemyGroup : public CameraActiveGroup {
public :
	EnemyGroup(CVGame *cvGame);
	virtual ~EnemyGroup();

	virtual void Update() override;

protected:
};