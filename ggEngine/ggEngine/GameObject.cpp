#include "GameObject.h"
#include "Body.h"
#include "Events.h"
#include "Debug.h"
#include "Group.h"
#include "Game.h"
#include "MemoryManager.h"
namespace ggEngine {
	GameObject::GameObject()
	{
		SetPosition(VECTOR_ZERO);
		SetScale(1,1);
		this->worldScale = Vector(1, 1);
		this->alive = true;
		this->rotate = 0;
		this->events = NULL;
		this->drawManager = nullptr;
	}
	GameObject::GameObject(Game *game)
	{
		SetPosition(VECTOR_ZERO);
		SetScale(1, 1);
		this->worldScale = Vector(1, 1);
		this->game = game;
		this->alive = true;
		this->rotate = 0;
		this->events = NULL;
		this->drawManager = game->GetDrawManager();
		this->spriteHandle = this->drawManager->GetSpriteHandle();
	}
	GameObject::~GameObject()
	{
		//g_debug.Log("Deleting GameObject");

		this->parentGroup->RemoveGameObjectFromDrawList(this);
		if (body != nullptr) {
			delete body;
		}
		if (events != NULL) delete events;
	}
	void GameObject::Draw()
	{
		g_debug.Warning("Draw method not implemented for this object " + this->name);
	}
	void GameObject::DrawRect()
	{
		g_debug.Warning("Draw mask method not implemented for this object " + this->name);

	}
	Vector GameObject::GetPosition()
	{
		return this->position;
	}
	Vector * GameObject::GetPositionAsRef()
	{
		return &this->position;
	}
	void GameObject::SetPosition(Vector vector)
	{
		this->position = vector;
	}
	void GameObject::SetPosition(double x, double y)
	{
		this->position.x = x;
		this->position.y = y;
	}
	void GameObject::Destroy()
	{
		GGObject::Destroy();
		this->game->memoryManager->AddObjectToRemoveQueue(this);
	}
	void GameObject::Transform(LPD3DXSPRITE spriteHandle)
	{
		//Scale from 0 0
		Matrix mat;
		mat = Matrix::CreateScaleMatrix(this->worldScale.x, this->worldScale.y);
		//Move to anchor
		mat *= Matrix::CreateTranslateMatrix(-this->GetWidth()*(this->GetAnchor().x), -this->GetHeight()*(this->GetAnchor().y));
		//Rotate around anchor
		mat *= Matrix::CreateRotateMatrix(this->rotate);
		//Translate to exact anchor and position
		//mat *= Matrix::CreateTranslateMatrix(this->position.x, this->position.y);
		mat *= Matrix::CreateTranslateMatrix(this->worldPosition.x, this->worldPosition.y);
		//Tranform to screen view
		//mat *= translatedWorldMatrix;

		//Vector scaleTransform(this->scale.x, this->scale.y);
		//Vector rotateCenter((this->width) / 2, (this->height) / 2);
		////Vector scaleCenter((this->width) / 2, (this->height) / 2);
		//Vector trans(this->position.x - this->width*(this->anchor.x), this->position.y - this->height*(this->anchor.y));
		//D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotateCenter, this->rotate, &trans);
		//mat *= (Matrix::CreateScaleMatrix(1, -1)*Matrix::CreateTranslateMatrix(0, this->height));
		/*if (this->body != NULL)
			this->body->rigidBody->Transform(mat);*/
		spriteHandle->SetTransform(&mat);
	}

	void GameObject::SetBody(Body * body)
	{
		if (this->body != nullptr) {
			delete this->body;
			this->body = nullptr;
		}
		if(this->parentGroup != nullptr) this->parentGroup->AddBodyToList(this->body);
		this->body = body;
	}

	void GameObject::SetParentObject(Group * parentGroup)
	{
		if (this->parentGroup != nullptr) {
			parentGroup->RemoveGameObjectFromDrawList(this);
			if (this->body != nullptr) {
				parentGroup->RemoveBodyFromList(this->body);
			}
		}
		this->parentGroup = parentGroup;
		SetTransformBasedOn(parentGroup);
		if (this->body != nullptr) {
			parentGroup->AddBodyToList(this->body);
		}
	}

	Rect GameObject::GetRect(bool isGetWorldRect)
	{
		int left, top, right, bottom;
		if (isGetWorldRect) {
			left = this->worldPosition.x + (-this->anchor.x)*GetWidth();
			top = this->worldPosition.y + (-this->anchor.y)*GetHeight();
		}
		else {
			left = this->position.x + (-this->anchor.x)*((GetWidth()));
			top = this->position.y + (-this->anchor.y)*((GetHeight()));
		}
		
		
		right = left + (1-anchor.x)*GetWidth();
		bottom = top + (1-anchor.y)*GetHeight();
		return Rect(left, top, right, bottom);
	}

	void GameObject::SetTransformBasedOn(GameObject * basePositionObject)
	{
		this->basePositionObject = basePositionObject;
	}

	void GameObject::UpdateWorldPosition(){
		this->worldScale = Vector(this->scale.x*this->basePositionObject->worldScale.x, this->scale.y*this->basePositionObject->worldScale.y);
		this->worldPosition = Vector(this->position.x*this->basePositionObject->worldScale.x, this->position.y*this->basePositionObject->worldScale.y) + this->basePositionObject->worldPosition;
		if (this->IsOpacityAffectByParent()) {
			this->opacity = this->basePositionObject->GetOpacity();
		}
	}
}
