#pragma once
#include "Sprite.h"
namespace ggEngine {
	class QuadNode;
	class TileMap;
	class SingleTile : public Sprite {
	public:
		SingleTile(DrawManager *drawManager, TileMap *tileMap ,SpriteInfo *image);
		SingleTile(DrawManager *drawManager, QuadNode *parentNode, SpriteInfo *image) :Sprite(drawManager) {}
		~SingleTile();
		void Draw();
	private:
	};
}