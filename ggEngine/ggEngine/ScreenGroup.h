#pragma once
#include "Group.h"
namespace ggEngine {
	class ScreenGroup : public Group {
	public:
		ScreenGroup();
		~ScreenGroup();
		void AddDrawObjectToList(GameObject* drawObject) override;
	};
}