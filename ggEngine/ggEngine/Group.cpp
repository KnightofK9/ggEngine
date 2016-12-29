#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "DrawManager.h"
#include "Text.h"
#include "Game.h"
#include "Body.h"
namespace ggEngine{
	Group::Group(Game *game) : GameObject(game)
	{
		SetOpacityAffectByParent(true);
	}
	Group::~Group(){
		auto cloneGroup = std::list<Group*>(this->groupList);
		for (auto it = cloneGroup.begin(); it != cloneGroup.end(); ++it)
		{
			delete *it;
		}
		groupList.clear();
		auto cloneGame = std::list<GameObject*>(this->drawList);
		for (auto it = cloneGame.begin(); it != cloneGame.end(); ++it)
		{
			delete *it;
		}
		drawList.clear();
	}

	void Group::AddGroup(Group * group)
	{
		Group* parentGroup = dynamic_cast<Group*>(group->GetParentObject());
		if (parentGroup != nullptr) parentGroup->GetGroupList()->remove(group);
		groupList.push_back(group);
		group->SetParentObject(this);
	}
	void Group::RemoveGroup(Group * group)
	{
		groupList.remove(group);
		group->SetParentObject(nullptr);
	}
	void Group::Update()
	{
		if (this->parentGroup != nullptr) {
			if (this->parentGroup->IsUsedMask()) {
				this->isUsedMask = true;
				if (this->position.y < 0) {
					this->position.x = 0;
				}
				else {
					double tempHeight = this->parentGroup->GetHeight() - this->GetHeight() + this->position.y;
					if (this->GetHeight() == 0 || tempHeight <= 0) {
						this->width = -tempHeight;
					}
				}
				if (this->position.x < 0) {
					this->position.x = 0;
				}
				else {
					double tempWidth = this->parentGroup->GetWidth() - this->GetWidth() + this->position.x;
					if (this->GetWidth() == 0 || tempWidth <= 0) {
						this->width = -tempWidth;
					}
				}
			}
			else {
				this->isUsedMask = false;
			}
		}
		if (this->update != nullptr) update();
		for (std::list<Group*>::const_iterator it = groupList.begin(); it != groupList.end(); it++)
		{
			(*it)->Update();
		}
	}
	void Group::AddDrawObjectToList(GameObject* drawObject){
		Sprite *sprite = dynamic_cast<Sprite*>(drawObject);
		if (sprite != nullptr) {
			sprite->style = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
		}
		else {
			Text *text = dynamic_cast<Text*>(drawObject);
			if (text != nullptr) {
				text->drawStyle = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
			}
		}



		//Group* parentGroup = dynamic_cast<Group*>(drawObject->GetParentObject());
	
		drawObject->SetParentObject(this);
		drawList.push_back(drawObject);
		RefreshCurrentCheckCollisionGroup(drawObject);
	}
	std::list<Body*> Group::GetBodyList()
	{
		std::list<Body*> allBodyList = this->bodyList;
		for (auto it = this->groupList.begin(); it != this->groupList.end(); ++it) {
			auto tBodyList = (*it)->GetBodyList();
			allBodyList.insert(allBodyList.end(), tBodyList.begin(), tBodyList.end());
		}
		return allBodyList;
	}
	void Group::Draw()
	{
		this->UpdateWorldPosition();
		if ((this)->IsVisible()) {
			this->drawManager->DrawList(this->GetDrawList(), this->isUsedMask);
			for (auto it = this->groupList.begin(); it != this->groupList.end();++it) {
				(*it)->Draw();
			}
		}
		
	}
	void Group::Reset(){

		for (std::list<GameObject*>::const_iterator it = drawList.begin(); it != drawList.end(); it++)
		{
			delete *it;
		}
		drawList.clear();
	}


	void Group::RemoveMask()
	{
		this->isUsedMask = false;
	}

	void Group::UpdatePhysics()
	{
		for (auto it = bodyList.begin(); it != bodyList.end();++it) {
			if ((*it)->IsAlive()) {
				if ((*it)->IsEnable()) {
					(*it)->Update();
				}
			}
		}
		for (auto it = this->groupList.begin(); it != this->groupList.end(); ++it) {
			if ((*it)->IsAlive()) {
				(*it)->UpdatePhysics();
			}
		}
	}

	void Group::AddBodyToList(Body * body)
	{
		this->bodyList.push_back(body);
	}

	void Group::AddGameObjectToDrawList(GameObject * go)
	{
		this->drawList.push_back(go);
		RefreshCurrentCheckCollisionGroup(go);

	}

	void Group::RemoveGameObjectFromDrawList(GameObject * go)
	{
		this->drawList.remove(go);
		if (go->body != nullptr) {
			go->body->ResetGroupCheckCollisionTo();
		}
	}

	void Group::RemoveBodyFromList(Body * body)
	{
		this->bodyList.remove(body);
	}

	void Group::AddGroupToCheckCollision(Group * group)
	{
		this->checkingCollisionGroup.push_back(group);
	}

	void Group::RemoveGroupToCheckCollision(Group * group)
	{
		this->checkingCollisionGroup.remove(group);
	}

	void Group::ResetGroupToCheckCollision()
	{
		this->checkingCollisionGroup.clear();
	}

	void Group::RefreshGroupToCheckCollision()
	{
		for (auto go : this->drawList) {
			go->body->ResetGroupCheckCollisionTo();
			for (auto group : this->checkingCollisionGroup) {
				go->body->AddGroupCheckCollisionTo(group);
			}
		}
	}

	void Group::RefreshCurrentCheckCollisionGroup(GameObject * go)
	{
		if (go->body != nullptr) {
			go->body->ResetGroupCheckCollisionTo();
			for (auto group : this->checkingCollisionGroup) {
				go->body->AddGroupCheckCollisionTo(group);
			}
		}
	}

	
	
}