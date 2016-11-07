#pragma once
#include <list>
#include "IGetGroup.h"
#include <functional>
#include "GameObject.h"
namespace ggEngine{
	class Sprite;
	class Group : public GameObject, public IGetGroup{
	public:
		Group();
		~Group();
		void Destroy();
		void AddGroup(Group* group);
		virtual void Update();
		std::function<void(void)> update;
		virtual void AddDrawObjectToList(GameObject* drawObject);
		virtual std::list<GameObject*> *GetDrawList() { return &this->drawList; }
		virtual std::list<Group*> *GetGroupList() { return &this->groupList; }
		void Reset();
	protected:
		std::list<Group*> groupList;
		std::list<GameObject*> drawList;
	private:
	};
}