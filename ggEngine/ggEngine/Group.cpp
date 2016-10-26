#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
namespace ggEngine{
	Group::Group()
	{
	}
	Group::~Group(){
		for (std::list<Group*>::const_iterator it = groupList.begin(); it != groupList.end(); it++)
		{
			delete *it;
		}
		groupList.clear();
		for (std::list<GameObject*>::const_iterator it = drawList.begin(); it != drawList.end(); it++)
		{
			delete *it;
		}
		drawList.clear();
	}
	void Group::Destroy(){
		GameObject::Destroy();
	}
	void Group::AddGroup(Group * group)
	{
		Group* parentGroup = dynamic_cast<Group*>(group->GetParentObject());
		if (parentGroup != NULL) parentGroup->GetGroupList()->remove(group);
		groupList.push_back(group);
		group->SetParentObject(this);
	}
	void Group::Update()
	{
		if (this->update != nullptr) update();
	}
	void Group::AddDrawObjectToList(GameObject* drawObject){
		drawList.push_back(drawObject);
	}
	void Group::Reset(){

		for (std::list<GameObject*>::const_iterator it = drawList.begin(); it != drawList.end(); it++)
		{
			delete *it;
		}
		drawList.clear();
	}
}