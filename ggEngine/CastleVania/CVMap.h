#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class CVMap : public Group {
public:
	CVMap(CVGame *cvGame);
	virtual ~CVMap();
	void BuildMap(const char* jsonChar);
	void Draw() override;
	void Update() override;
	void UpdatePhysics() override;
private:
	TileMap *tileMapGroup;
	QuadTree *quadTreeGroup;
	Group* movingGroup;
	Add* add;
};