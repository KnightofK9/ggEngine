#include "DrawableGraphic.h"




DrawableGraphic::DrawableGraphic(float x, float y, GraphicInfo graphicInfo) :GameObject(x, y)
{
	this->graphicInfo = graphicInfo;
}


void DrawableGraphic::destroy()
{
}
