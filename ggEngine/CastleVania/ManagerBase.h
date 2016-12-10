#pragma once
#include <ggEngine.h>
#include "CVGame.h"
using namespace ggEngine;
class ManagerBase {
public:
	ManagerBase(CVGame *cvGame);
	~ManagerBase();
protected:

	Cache *cache = nullptr;
	Add* add = nullptr;
	Preload *preload = nullptr;

	CVGame *cvGame = nullptr;
};