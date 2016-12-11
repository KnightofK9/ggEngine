#pragma once
#include "Group.h"
namespace ggEngine{
	class Game;
	class World : public Group{
	public:
		World(Game *game,double width = GAME_WIDTH, double height = GAME_HEIGHT);
		virtual ~World();
		void Reset();
		void UpdateWorldPosition() override;
	private:
	};
}