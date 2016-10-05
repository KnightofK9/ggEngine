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
}
