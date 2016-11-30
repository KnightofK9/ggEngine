#pragma once
#include <ggEngine.h>
#include "Simon.h"
#include "CVGame.h"
#include "InfoPanel.h"
using namespace ggEngine;
class CVState;
class CVAdd : public Add {
public:
	CVAdd(CVState* state, CVGame *game);
	virtual ~CVAdd();
	Simon* CharSimon(double x, double y, int health, InfoPanel *infoPanel, ggEngine::Group *group);
	InfoPanel* UIInfoPanel(ggEngine::Group *group);
	HealthBar *UIPlayerHealthBar(double x, double y, ggEngine::Group* group);
	HealthBar *UIEnemyHealthBar(double x, double y, ggEngine::Group* group);

private:
	CVGame *cvgame;
	CVState* state;
	ggEngine::Audio *audio;
};