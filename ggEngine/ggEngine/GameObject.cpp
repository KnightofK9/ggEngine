#include "GameObject.h"

namespace ggEngine {
	GameObject::GameObject()
	{
		SetPosition(VECTOR_ZERO);
		SetVelocity(VECTOR_ZERO);
		this->alive = true;
	}
	GameObject::~GameObject()
	{

	}
	Vector3 GameObject::GetPosition()
	{
		return this->position;
	}
	void GameObject::SetPosition(Vector3 vector)
	{
		this->position = vector;
	}
	void GameObject::SetPosition(double x, double y)
	{
		this->position.setX(x);
		this->position.setY(y);
	}
	void GameObject::SetVelocity(Vector3 vector)
	{
		this->velocity = vector;
	}
	Vector3 GameObject::GetVelocity()
	{
		return this->velocity;
	}
	void GameObject::Destroy()
	{
		this->alive = false;
	}
}
