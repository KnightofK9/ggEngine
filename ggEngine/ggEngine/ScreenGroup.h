#pragma once
#include "Group.h"
namespace ggEngine {
	class DrawManager;
	class ScreenGroup : public Group {
	public:
		ScreenGroup(DrawManager *drawManager);
		~ScreenGroup();
		void AddDrawObjectToList(GameObject* drawObject) override;
	};
}