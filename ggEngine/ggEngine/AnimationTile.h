#pragma once
#include "Sprite.h"
#include <vector>
namespace ggEngine {
	class SingleTile;
	class TileMap;
	class Game;
	class AnimationTile : public Sprite {
	public:
		AnimationTile(Game *game, TileMap *tileMap);
		virtual ~AnimationTile();
		void AddTileAnimation(SingleTile* singleTile);
		void Draw();
	private:
		std::vector<SingleTile*> tileAnimationList;
		int currentAnim;
		int size;
	};
}