#pragma once
#include <list>
#include "IGetGroup.h"
#include <functional>
#include "GameObject.h"
namespace ggEngine{
	class Sprite;
	class DrawManager;
	class Game;
	class Body;
	class Group : public GameObject, public IGetGroup{
	public:
		Group(Game *game);
		virtual ~Group();
		void AddGroup(Group* group);
		virtual void Update();
		std::function<void(void)> update;
		virtual void AddDrawObjectToList(GameObject* drawObject);
		virtual std::list<GameObject*> GetDrawList() { return this->drawList; }
		virtual std::list<Group*> *GetGroupList() { return &this->groupList; }
		virtual std::list<Body*> GetBodyList();
		virtual void Draw() override;
		void Reset();
		void SetMask(bool isUsedMask) { this->isUsedMask = isUsedMask; }
		bool IsUsedMask() { return this->isUsedMask; }
		void RemoveMask();
		virtual void UpdatePhysics();
		void AddBodyToList(Body *body);

		virtual void AddGameObjectToDrawList(GameObject *go);
		virtual void RemoveGameObjectFromDrawList(GameObject *go);

		void RemoveBodyFromList(Body *body);

	protected:
		RECT mask;
		bool isUsedMask = false;
		std::list<Group*> groupList;
		std::list<GameObject*> drawList;
		std::list<Body*> bodyList;
	private:
	};
}