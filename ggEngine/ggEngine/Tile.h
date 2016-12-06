#pragma once
#include "Sprite.h"
namespace ggEngine {
	class Game;
	class Tile : public Sprite {
	public:
		Tile(Game *game, SpriteInfo * image);
		~Tile();

		void Draw(double x, double y);

	private:

	};
}