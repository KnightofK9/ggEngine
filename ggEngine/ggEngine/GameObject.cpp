#include "GameObject.h"
#include "Body.h"
#include "Events.h"
namespace ggEngine {
	GameObject::GameObject()
	{
		SetPosition(VECTOR_ZERO);
		SetScale(1,1);
		this->alive = true;
		this->rotate = 0;
		this->events = NULL;
	}
	GameObject::~GameObject()
	{
		if (body!=NULL) delete body;
		if (events != NULL) delete events;
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
	void GameObject::SetPosition(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;
	}
	void GameObject::Destroy()
	{
		this->alive = false;
	}
	void GameObject::Transform(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle)
	{
		//Scale from 0 0
		Matrix mat;
		mat = Matrix::CreateScaleMatrix(this->scale.x, this->scale.y);
		//Move to anchor
		mat *= Matrix::CreateTranslateMatrix(-this->GetWidth()*(this->GetAnchor().x), -this->GetHeight()*(this->GetAnchor().y));
		//Rotate around anchor
		mat *= Matrix::CreateRotateMatrix(this->rotate);
		//Translate to exact anchor and position
		//mat *= Matrix::CreateTranslateMatrix(this->position.x, this->position.y);
		mat *= Matrix::CreateTranslateMatrix(this->worldPosition.x, this->worldPosition.y);
		//Tranform to screen view
		mat *= translatedWorldMatrix;

		//Vector scaleTransform(this->scale.x, this->scale.y);
		//Vector rotateCenter((this->width) / 2, (this->height) / 2);
		////Vector scaleCenter((this->width) / 2, (this->height) / 2);
		//Vector trans(this->position.x - this->width*(this->anchor.x), this->position.y - this->height*(this->anchor.y));
		//D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotateCenter, this->rotate, &trans);
		//mat *= (Matrix::CreateScaleMatrix(1, -1)*Matrix::CreateTranslateMatrix(0, this->height));
		if (this->body != NULL)
			this->body->rigidBody->Transform(mat);
		spriteHandle->SetTransform(&mat);
	}

	void GameObject::UpdateWorldPosition(){
		this->worldPosition = this->position + this->parentObject->worldPosition;
	}
}
