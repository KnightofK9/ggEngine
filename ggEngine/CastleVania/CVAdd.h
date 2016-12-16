#pragma once
#include <ggEngine.h>
#include "Simon.h"
#include "ManagerBase.h"
#include "InfoPanel.h"
#include "CVMap.h"
#include "GameOverScreen.h"
#include "SimonGroup.h"
using namespace ggEngine;
class CVState;
class CVAdd : public ManagerBase {
public:
	CVAdd(CVGame *game);
	virtual ~CVAdd();
	Simon* CharSimon(double x, double y, int health, InfoPanel *infoPanel, ggEngine::Group *group);
	InfoPanel* UIInfoPanel(GameOverScreen *goScreen , ggEngine::Group *group);
	HealthBar *UIPlayerHealthBar(double x, double y, ggEngine::Group* group);
	HealthBar *UIEnemyHealthBar(double x, double y, ggEngine::Group* group);
	CVMap *LoadMap(const char* json, ggEngine::Group* group);
	GameOverScreen *UIGameOverScreen(ggEngine::Group* group);
	SimonGroup *AddSimonGroup();

private:

	ggEngine::Audio *audio;
};