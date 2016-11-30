#include "SpriteInfo.h"
#include "Texture.h"
ggEngine::SpriteInfo::SpriteInfo(Texture * texture)
{
	this->texture = texture;
	this->width = texture->GetWidth();
	this->height = texture->GetHeight();
	this->srcRect = { 0,0,(long)width, (long)height };
	this->type = SpriteType_Texture;
}

ggEngine::SpriteInfo::SpriteInfo(Texture * atlas, float x, float y, float width, float height)
{
	this->texture = atlas;
	this->width = width;
	this->height = height;
	this->srcRect = { (long)x, (long)y, (long)(x + width),(long)(y + height) };
	this->type = SpriteType_Atlas;
}

ggEngine::SpriteInfo::~SpriteInfo()
{
	Release();
}

void ggEngine::SpriteInfo::Release()
{
	if (this->texture != NULL) {
		delete this->texture;
		this->texture = NULL;
	}
}
