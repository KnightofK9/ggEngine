#pragma once
#include "Group.h"
namespace ggEngine {
	class DrawManager;
	class Game;
	class ScreenGroup : public Group {
	public:
		ScreenGroup(Game *game);
		~ScreenGroup();
		virtual void AddDrawObjectToList(GameObject* drawObject) override;
	};
}