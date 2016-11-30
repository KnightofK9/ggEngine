#pragma once
#include <list>
#include "IGetGroup.h"
#include <functional>
#include "GameObject.h"
namespace ggEngine{
	class Sprite;
	class DrawManager;
	class Game;
	class Group : public GameObject, public IGetGroup{
	public:
		Group(Game *game);
		virtual ~Group();
		void AddGroup(Group* group);
		virtual void Update();
		std::function<void(void)> update;
		virtual void AddDrawObjectToList(GameObject* drawObject);
		virtual std::list<GameObject*> *GetDrawList() { return &this->drawList; }
		virtual std::list<Group*> *GetGroupList() { return &this->groupList; }
		virtual void Draw() override;
		void Reset();
		void SetMask(bool isUsedMask) { this->isUsedMask = isUsedMask; }
		bool IsUsedMask() { return this->isUsedMask; }
		void RemoveMask();
		void RemoveObjectFromList(GameObject*go);
	protected:
		RECT mask;
		bool isUsedMask = false;
		std::list<Group*> groupList;
		std::list<GameObject*> drawList;
	private:
	};
}