#pragma once
#include <list>
#include "IGetGroup.h"
#include <functional>
#include "DrawObject.h"
namespace ggEngine{
	class Sprite;
	class Group : public GameObject, public IGetGroup{
	public:
		Group();
		~Group();
		void Destroy();
		void AddGroup(Group* group);
		void Update();
		std::function<void(void)> update;
		void AddDrawObjectToList(DrawObject* drawObject);
		std::list<DrawObject*> *GetDrawList() { return &this->drawList; }
		std::list<Group*> *GetGroupList() { return &this->groupList; }
		void Reset();
	protected:
		std::list<Group*> groupList;
	private:
		std::list<DrawObject*> drawList;
	};
}