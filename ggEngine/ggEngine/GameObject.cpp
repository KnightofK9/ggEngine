#include "GameObject.h"

namespace ggEngine {
	GameObject::GameObject()
	{
		SetPosition(VECTOR_ZERO);
		SetVelocity(VECTOR_ZERO);
		SetScale(1,1);
		this->alive = true;
		this->rotate = 0;
	}
	GameObject::~GameObject()
	{

	}
	Vector GameObject::GetPosition()
	{
		return this->position;
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
	void GameObject::SetVelocity(Vector vector)
	{
		this->velocity = vector;
	}
	Vector GameObject::GetVelocity()
	{
		return this->velocity;
	}
	void GameObject::Destroy()
	{
		this->alive = false;
	}
}
