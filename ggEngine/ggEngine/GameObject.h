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
		virtual void SetWidth(float width){ this->width = width; }
		virtual void SetHeight(float height){ this->height = height; }
		virtual float GetWidth(){ return this->width; }
		virtual float GetHeight(){ return this->height; }
		void SetAnchor(float x, float y) { this->anchor.x = x; this->anchor.y = y; }
		Vector GetAnchor() { return this->anchor; }
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		void Destroy();
		Vector GetScale() { return this->scale; }
		virtual void Transform(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle);
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
		float width;
		float height;
		Vector anchor;
		Vector scale;
		bool alive;
		bool visible;
		float rotate;
	};
}