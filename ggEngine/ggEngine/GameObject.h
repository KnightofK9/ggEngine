#pragma once
#include "Vector.h"
#include "ConstantEnum.h"
#include "GGObject.h"
#include <string>
#include "Events.h"
namespace ggEngine {
	class Body;
	class GameObject :public GGObject {
	public:
		GameObject();
		~GameObject();
		Vector GetPosition();
		Vector* GetPositionAsRef();
		virtual void SetPosition(Vector vector);
		virtual void SetPosition(double x, double y);
		virtual void SetX(double x) { this->position.x = x; }
		virtual void SetY(double y) { this->position.y = y; }
		virtual double GetX() { return this->position.x; }
		virtual double GetY() { return this->position.y; }
		virtual void SetWidth(double width){ this->width = width; }
		virtual void SetHeight(double height){ this->height = height; }
		virtual double GetWidth(){ return this->width; }
		virtual double GetHeight(){ return this->height; }
		void SetAnchor(double x, double y) { this->anchor.x = x; this->anchor.y = y; }
		void UpdateWorldPosition();
		Vector GetAnchor() { return this->anchor; }
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		void Destroy();
		Vector GetScale() { return this->scale; }
		virtual void Transform(LPD3DXSPRITE spriteHandle);
		virtual void SetScale(Vector vector) { this->scale = vector; }
		virtual void SetScale(double x, double y){ this->scale.x = x; this->scale.y = y; }
		virtual void SetRotate(double angle){ this->rotate = angle; }
		double GetRotate(){ return this->rotate; }
		bool IsAlive() { return this->alive; }
		Body* body = NULL;
		Events* events = NULL;
		Vector position;
		Vector worldPosition;
		std::string name = "";
		void SetParentObject(GameObject *parentObject){this->parentObject = parentObject;}
		GameObject *GetParentObject(){ return this->parentObject; }
	protected:
		GameObject* parentObject = NULL;
		double width;
		double height;
		Vector anchor;
		Vector scale;
		bool alive;
		bool visible;
		double rotate;
	};
}