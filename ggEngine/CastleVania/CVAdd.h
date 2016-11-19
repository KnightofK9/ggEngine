#pragma once
#include <ggEngine.h>
#include "Simon.h"
#include "CVGame.h"
using namespace ggEngine;
class CVState;
class CVAdd : public Add {
public:
	CVAdd(CVState* state, CVGame *game);
	~CVAdd();
	Simon* CharSimon(double x, double y, ggEngine::Group *group);
private:
	CVGame *cvgame;
	CVState* state;
};