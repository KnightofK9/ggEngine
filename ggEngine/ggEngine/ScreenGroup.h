#pragma once
#include "Group.h"
namespace ggEngine {
	class DrawManager;
	class Game;
	class ScreenGroup : public Group {
	public:
		ScreenGroup(Game *game);
		virtual ~ScreenGroup();
		virtual void AddDrawObjectToList(GameObject* drawObject) override;
	};
}