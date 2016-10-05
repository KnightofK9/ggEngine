#include "DrawObject.h"

ggEngine::DrawObject::DrawObject(DrawManager* drawManager)
{
	this->drawManager = drawManager; 
	this->spriteHandle = drawManager->GetSpriteHandle();
}

ggEngine::DrawObject::~DrawObject()
{
}
