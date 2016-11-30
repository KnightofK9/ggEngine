#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "DrawManager.h"
#include "Text.h"
#include "Game.h"
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
	void Group::Update()
	{
		if (this->parentObject != nullptr) {
			if (this->parentObject->IsUsedMask()) {
				this->isUsedMask = true;
				if (this->position.y < 0) {
					this->position.x = 0;
				}
				else {
					double tempHeight = this->parentObject->GetHeight() - this->GetHeight() + this->position.y;
					if (this->GetHeight() == 0 || tempHeight <= 0) {
						this->width = -tempHeight;
					}
				}
				if (this->position.x < 0) {
					this->position.x = 0;
				}
				else {
					double tempWidth = this->parentObject->GetWidth() - this->GetWidth() + this->position.x;
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



		Group* parentGroup = dynamic_cast<Group*>(drawObject->GetParentObject());
		if (parentGroup != nullptr) parentGroup->GetDrawList()->remove(drawObject);
		drawObject->SetParentObject(this);
		drawList.push_back(drawObject);
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

	void Group::RemoveObjectFromList(GameObject *go)
	{
		this->drawList.remove(go);
	}
	
}