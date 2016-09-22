#pragma once
#include <list>
#include "DrawObject.h"
namespace ggEngine{
	class DrawManager;
	class Sprite;
	class Group : public GameObject{
	public:
		Group(DrawManager *drawManager);
		~Group();
		void Destroy();
		void AddSpriteToList(Sprite* sprite);
	private:
		std::list<DrawObject*> drawList;
		DrawManager *drawManager;
	};
}