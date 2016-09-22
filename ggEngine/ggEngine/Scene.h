#pragma once
#include "GGObject.h"
#include <list>
namespace ggEngine{
	class Group;
	class Scene : public GGObject{
	public:
		Scene();
		~Scene();
		virtual void Destroy();
		std::list<Group*> getGroupList(){ return this->groupList; }
	protected:
		virtual void Init();
		virtual void Preload(); 
		virtual void LoadComplete();
	private:
		std::list<Group*> groupList;
	};
}