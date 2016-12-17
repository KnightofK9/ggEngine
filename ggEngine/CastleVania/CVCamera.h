#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVCamera : public Camera {
public:
	CVCamera(Game *game, int width, int height, double x = 0, double y = 0, bool enableManualMove = false);
	~CVCamera();
private:
};