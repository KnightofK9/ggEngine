#pragma once
#include <list>
#include "DrawObject.h"
#include "DrawManager.h"
namespace ggEngine{
	class Group : public GameObject{
	public:
		Group(DrawManager *drawManager);
		~Group();
		void Destroy();
	private:
		std::list<DrawObject*> drawList;
		DrawManager *drawManager;
	};
}