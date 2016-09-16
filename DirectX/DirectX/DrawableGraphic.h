#pragma once
#include "GameObject.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicInfo.h"
#pragma comment(lib, "d3d9.lib")
class DrawableGraphic : public GameObject{
public:
	DrawableGraphic(float x, float y, GraphicInfo graphicInfo);
	void destroy();

protected:
	GraphicInfo graphicInfo;
};