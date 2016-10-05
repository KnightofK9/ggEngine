#pragma once
#include "Vector.h"
#include "ConstantEnum.h"
#include "GGObject.h"
#include <string>
namespace ggEngine {
	class Events;
	class Body;
	class GameObject :public GGObject {
	public:
		GameObject();
		~GameObject();
		Vector GetPosition();
		Vector* GetPositionAsRef();
		virtual void SetPosition(Vector vector);
		virtual void SetPosition(float x, float y);
		virtual void SetX(float x) { this->position.x = x; }
		virtual void SetY(float y) { this->position.y = y; }
		virtual float GetX() { return this->position.x; }
		virtual float GetY() { return this->position.y; }
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		void Destroy();
		Vector GetScale() { return this->scale; }
		virtual void SetScale(Vector vector) { this->scale = vector; }
		virtual void SetScale(float x, float y){ this->scale.x = x; this->scale.y = y; }
		virtual void SetRotate(float angle){ this->rotate = angle; }
		float GetRotate(){ return this->rotate; }
		bool IsAlive() { return this->alive; }
		Events* events = NULL;
		Body* body = NULL;
		Vector position;
		std::string name = "";
	protected:
		Vector scale;
		bool alive;
		bool visible;
		float rotate;
	};
}