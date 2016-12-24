#pragma once
#include <ggEngine.h>
#include "ManagerBase.h"
#include "AxeKnight.h"
#include "MedusaHead.h"
#include "BatEnemy.h"
#include "AI6.h"
#include "AI7.h"
#include "Ghost.h"
#include "EnemyBase.h"
#include "BonePillar.h"
#include "Medusa.h"
using namespace ggEngine;
class EnemyManager : ManagerBase {
public:
	EnemyManager(CVGame *cvGame);
	~EnemyManager();

	void PreloadAll();
	AxeKnight* AddAxeKnight(double x, double y, Group *group);
	MedusaHead* AddMedusaHead(double x, double y, Group *group);
	BatEnemy* AddBatEnemy(double x, double y, Group* group);
	Ghost* AddGhost(double x, double y, Group* group);
	AI6* AddAI6(double x, double y, double moveWidth, Group* group);
	AI7* AddAI7(double x, double y, Group* group);
	BonePillar* AddBonePillar(double x, double y, Group* group);
	Medusa* AddMedusa(double x, double y, Group* group);

private:
};