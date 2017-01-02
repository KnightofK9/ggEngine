#include "CVMapManager.h"
#include "CVAdd.h"
#include "GameOverScreen.h"
#include "InfoPanel.h"
#include "AnimationManager.h"
CVMapManager::CVMapManager(CVGame * cvGame) : ManagerBase(cvGame)
{
}

CVMapManager::~CVMapManager()
{
}

void CVMapManager::PreloadAll()
{
	{
		PreloadMap("level-2", "State/level2-tilemap.json");
		PreloadMap("level-3", "State/level3-tilemap.json");
		PreloadMap("test-state", "State/TestState.json");
		//Json state0("State/TestState.json", true);
		//Json state("State/level2-tilemap.json", true);
		//Json state2("State/level3-tilemap.json", true);
		//cvMap = this->cvAdd->LoadMap("State", state0.GetCharArray().c_str(), nullptr);
		//cvMap1 = this->cvAdd->LoadMap("level-2", state.GetCharArray().c_str(), nullptr);
		//cvMap2 = this->cvAdd->LoadMap("level-3", state2.GetCharArray().c_str(), nullptr);
	}
}

CVMap* CVMapManager::StartMap(std::string mapName)
{
	 CVMap* cvMap = nullptr;
	 auto it = this->mapDict.find(mapName);
	 if (it == this->mapDict.end()) {
		 g_debug.Error("Error, no map found with name " + mapName);
		 return cvMap;
	 }
	 cvMap = (*it).second;
	 if (this->cvGame->simon->currentMap != nullptr) this->cvGame->simon->currentMap->DeActive();
	 this->cvGame->animationManager->simonGroup = cvMap->simonGroup;
	 cvMap->LoadSimon(this->infoPanel, this->goScreen, this->cvGame->simon);
	 cvMap->Active();
	 return cvMap;

}

void CVMapManager::LoadUI(GameOverScreen * goScreen, InfoPanel * infoPanel)
{
	this->goScreen = goScreen;
	this->infoPanel = infoPanel;
}

CVMap* CVMapManager::PreloadMap(std::string mapName, std::string jsonPath, bool isStart)
{
	Json state(jsonPath, true);
	auto cvMap = this->cvGame->cvAdd->LoadMap(mapName, state.GetCharArray().c_str(), nullptr);
	this->mapDict[mapName] = cvMap;
	if (isStart) {
		return StartMap(mapName);
	}
	return cvMap;
}
