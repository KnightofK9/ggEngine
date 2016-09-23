#pragma once
#include <list>
#include "DrawObject.h"
#include "IGetGroup.h"
namespace ggEngine{
	class DrawManager;
	class Sprite;
	class Group : public GameObject, public IGetGroup{
	public:
		Group(DrawManager *drawManager);
		~Group();
		void Destroy();
		void AddSpriteToList(Sprite* sprite);
		std::list<Group*> *GetGroupList() { return &this->groupList; }
	private:
		std::list<DrawObject*> drawList;
		std::list<Group*> groupList;
		DrawManager *drawManager;
	};
}