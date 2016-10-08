#include "SpriteInfo.h"
#include "Texture.h"
ggEngine::SpriteInfo::SpriteInfo(Texture * texture)
{
	this->texture = texture;
	this->width = texture->GetWidth();
	this->height = texture->GetHeight();
	this->srcRect = { 0,0,width, height };
	this->type = SpriteType_Texture;
}

ggEngine::SpriteInfo::SpriteInfo(Texture * atlas, float x, float y, float width, float height)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->srcRect = { x,y,x + width,y + height };
	this->type = SpriteType_Atlas;
}

ggEngine::SpriteInfo::~SpriteInfo()
{
	Release();
}

void ggEngine::SpriteInfo::Release()
{
	this->texture->Destroy();
}
