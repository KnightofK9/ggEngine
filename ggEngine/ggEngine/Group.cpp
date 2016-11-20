#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "DrawManager.h"
namespace ggEngine{
	Group::Group(DrawManager *drawManager) : GameObject(drawManager)
	{
		SetOpacityAffectByParent(true);
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

		Group* parentGroup = dynamic_cast<Group*>(drawObject->GetParentObject());
		if (parentGroup != NULL) parentGroup->GetDrawList()->remove(drawObject);
		drawObject->SetParentObject(this);
		drawList.push_back(drawObject);
	}
	void Group::Draw()
	{
		this->UpdateWorldPosition();
		if ((this)->IsVisible()) {
			for (auto it = this->groupList.begin(); it != this->groupList.end();++it) {
				(*it)->Draw();
			}
			this->drawManager->DrawList(this->GetDrawList());
		}
		
	}
	void Group::Reset(){

		for (std::list<GameObject*>::const_iterator it = drawList.begin(); it != drawList.end(); it++)
		{
			delete *it;
		}
		drawList.clear();
	}
	
}