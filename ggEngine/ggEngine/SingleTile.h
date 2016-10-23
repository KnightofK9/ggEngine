#pragma once
#include "Sprite.h"
namespace ggEngine {
	class TileMap;
	class SingleTile : public Sprite {
	public:
		SingleTile(DrawManager *drawManager,TileMap *tileMap ,SpriteInfo *image);
		~SingleTile();
		void Draw();
	private:
	};
}