#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVBlock;
class CVCamera : public Camera {
public:
	CVCamera(Game *game, int width, int height, double x = 0, double y = 0, bool enableManualMove = false);
	~CVCamera();

	void SetBlock(CVBlock *block);
	void Update() override;
private:
	CVBlock *block = nullptr;
};