#pragma once
#include <map>
#include "ManagerBase.h"
class CVMap;
class GameOverScreen;
class InfoPanel;
class CVMapManager : ManagerBase {
public:
	CVMapManager(CVGame *cvGame);
	~CVMapManager();

	void PreloadAll();
	CVMap* PreloadMap(std::string mapName, std::string jsonPath, bool isStart = false);
	CVMap* StartMap(std::string mapName);
	void LoadUI(GameOverScreen  *goScreen, InfoPanel *infoPanel);
private:
	GameOverScreen *goScreen = nullptr;
	InfoPanel *infoPanel = nullptr;
	std::map<std::string,CVMap*> mapDict;

};