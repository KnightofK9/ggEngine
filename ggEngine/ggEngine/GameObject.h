#pragma once
#include "Vector3.h"
#include "ConstantEnum.h"
#include "GGObject.h"
namespace ggEngine {
	class GameObject :public GGObject {
	public:
		GameObject();
		~GameObject();
		Vector3 GetPosition();
		void SetPosition(Vector3 vector);
		void SetPosition(double x, double y);
		void SetX(double x) { this->position.setX(x); }
		void SetY(double y) { this->position.setY(y); }
		double GetX() { return this->position.getX(); }
		double GetY() { return this->position.getY(); }
		void SetVelocity(Vector3 vector);
		Vector3 GetVelocity();
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		void Destroy();
		Vector3 GetScale() { return this->scale; }
		void SetScale(Vector3 vector) { this->scale = vector; }
	private:
		Vector3 position;
		Vector3 velocity;
		Vector3 scale;
		bool alive;
		bool visible;
	};
}