#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class InfoPanel;
class CVMap : public Group {
public:
	CVMap(CVGame *cvGame);
	virtual ~CVMap();
	void BuildMap(const char* jsonChar);
	void Draw() override;
	void Update() override;
	void UpdatePhysics() override;
	void LoadSimon(InfoPanel *infoPanel, Simon *simon = nullptr);
	TileMap *tileMapGroup;
	QuadTree *quadTreeGroup;
	CameraActiveGroup* cameraActiveGroup;
	Group *simonGroup;
	Simon* simon;
private:
	InfoPanel *infoPanel;
	Add* add;
	CVAdd* cvAdd;
	CVGame* cvGame;
};