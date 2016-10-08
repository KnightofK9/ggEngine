#pragma once
#include "GGObject.h"
#include <d3d9.h>
#include "SpriteType.h"
namespace ggEngine {
	class Texture;
	class SpriteInfo: public GGObject {
	public:
		SpriteInfo(Texture *texture);
		SpriteInfo(Texture *atlas, float x, float y, float width, float height);
		~SpriteInfo();
		float GetWidth() { return this->width; }
		float GetHeight() { return this->height; }
		RECT GetRect() { return this->srcRect; }
		Texture *GetTexture() { return this->texture; }
		void Release();
		SpriteType GetType() { return this->type; }
	private:
		float width;
		float height;
		Texture *texture;
		RECT srcRect;
		SpriteType type;
	};
}