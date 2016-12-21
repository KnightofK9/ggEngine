#pragma once
#include <ggEngine.h>
#include "ManagerBase.h"
using namespace ggEngine;
class EnemyManager : ManagerBase {
public:
	EnemyManager(CVGame *cvGame);
	~EnemyManager();

	void PreloadAll();
private:
};