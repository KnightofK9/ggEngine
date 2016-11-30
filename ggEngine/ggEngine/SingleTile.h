#pragma once
#include "Sprite.h"
namespace ggEngine {
	class QuadNode;
	class TileMap;
	class Game;
	class SingleTile : public Sprite {
	public:
		SingleTile(Game *game, TileMap *tileMap ,SpriteInfo *image);
		SingleTile(Game *game, QuadNode *parentNode, SpriteInfo *image) :Sprite(game) {}
		virtual ~SingleTile();
		void Draw();
	private:
	};
}