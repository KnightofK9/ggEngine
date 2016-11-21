#pragma once
#include "Group.h"
namespace ggEngine {
	class DrawManager;
	class ScreenGroup : public Group {
	public:
		ScreenGroup(DrawManager *drawManager);
		~ScreenGroup();
		virtual void AddDrawObjectToList(GameObject* drawObject) override;
	};
}