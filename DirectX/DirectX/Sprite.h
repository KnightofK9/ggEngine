#pragma once
#include <string>
#include "Point.h"
#include "DrawableGraphic.h"
class Sprite : public DrawableGraphic {
public:
	Sprite(float x, float y, GraphicInfo graphicInfo);
	void setAnchor(float x, float y);
private:
	Point anchor;
};