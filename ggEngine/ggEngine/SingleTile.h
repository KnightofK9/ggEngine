#pragma once
#include "Sprite.h"
namespace ggEngine {
	class QuadNode;
	class SingleTile : public Sprite {
	public:
		SingleTile(DrawManager *drawManager, QuadNode *parentNode ,SpriteInfo *image);
		~SingleTile();
		void Draw();
	private:
	};
}