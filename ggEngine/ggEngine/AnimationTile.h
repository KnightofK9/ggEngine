#pragma once
#include "Sprite.h"
#include <vector>
namespace ggEngine {
	class SingleTile;
	class TileMap;
	class AnimationTile : public Sprite {
	public:
		AnimationTile(DrawManager *drawManager, TileMap *tileMap);
		~AnimationTile();
		void AddTileAnimation(SingleTile* singleTile);
		void Draw();
	private:
		std::vector<SingleTile*> tileAnimationList;
		int currentAnim;
		int size;
	};
}