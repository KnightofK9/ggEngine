#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class InfoPanel;
class SimonGroup;
class CVStage;
class CVCamera;
class CVBlock;
class EnemyGroup;
class Door;
class CVMap : public Group {
public:
	CVMap(CVGame *cvGame);
	virtual ~CVMap();
	void BuildMap(const char* jsonChar, int level = -1);
	void Draw() override;
	void Update() override;
	void UpdatePhysics() override;
	void LoadSimon(InfoPanel *infoPanel, GameOverScreen *goScreen, Simon *simon = nullptr);
	TileMap *tileMapGroup;
	QuadTree *quadTreeGroup;
	CameraActiveGroup* cameraActiveGroup;
	SimonGroup *simonGroup;
	Simon* simon;
	EnemyGroup *enemyGroup;
	void SetStage(int stageNumber, int blockNumber = 0, bool isRestartState = false);
	void SetBlock(int blockNumber, bool isRestartState = false);
	void OnOutOfBlock(Rect r = Rect(-1,-1,-1,-1));
	void OnNextLevel(int levelIndex);
	void OnNextBlock(int blockIndex);
	void OnNextStage(int stageIndex, int blockIndex = 0);
	void OnFallOutOfMap();
	void OnEnterDoor(Door *door);
private:
	void CheckIfSimonOutOfBlock();
	void StartSwitchingState();
	int levelNumber;
	CVStage* currentStage = nullptr;
	void SetSimonPositionOnChangeBlock();
	CVBlock* currentBlock = nullptr;
	InfoPanel *infoPanel;
	Add* add;
	CVAdd* cvAdd;
	CVGame* cvGame;
	CVCamera* camera;
	bool isSwitchingStage = false;
	std::vector<CVStage*> stageList;
	Door* door = nullptr;
};