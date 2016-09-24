#pragma once
#include <list>
#include "DrawObject.h"
#include "IGetGroup.h"
#include <functional>
namespace ggEngine{
	class DrawManager;
	class Sprite;
	class Group : public GameObject, public IGetGroup{
	public:
		Group(DrawManager *drawManager);
		~Group();
		void Destroy();
		void Update();
		std::function<void(void)> update;
		void AddSpriteToList(Sprite* sprite);
		std::list<DrawObject*> *GetDrawList() { return &this->drawList; }
		std::list<Group*> GetGroupList() { return this->groupList; }
	private:
		std::list<DrawObject*> drawList;
		std::list<Group*> groupList;
		DrawManager *drawManager;
	};
}