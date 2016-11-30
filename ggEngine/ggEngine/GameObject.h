#pragma once
#include "Vector.h"
#include "ConstantEnum.h"
#include "GGObject.h"
#include <string>
#include "Events.h"
#include <d3d9.h>
#include "DrawManager.h"
#include "Matrix.h"
#include "Rect.h"
namespace ggEngine {
	class Body;
	class Game;
	typedef unsigned int Tag;
	class GameObject :public GGObject {
	public:
		GameObject();
		GameObject(Game *game);
		virtual ~GameObject();

		virtual void Destroy() override;

		virtual void Draw();
		virtual void DrawRect();
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
		virtual void UpdateWorldPosition();
		Vector GetAnchor() { return this->anchor; }
		void SetVisible(bool visible) { this->visible = visible; }
		bool IsVisible() { return this->visible; }
		Vector GetScale() { return this->scale; }
		virtual void Transform(LPD3DXSPRITE spriteHandle);
		virtual void SetScale(Vector vector) { this->scale = vector; }
		virtual void SetScale(double x, double y){ this->scale.x = x; this->scale.y = y; }
		virtual void SetRotate(double angle){ this->rotate = angle; }
		double GetRotate(){ return this->rotate; }
		
		void SetBody(Body* body) { this->body = body; }
		Body* GetBody() { return this->body; }
		Body* body = NULL;
		Events* events = NULL;
		Vector position;
		Vector worldPosition;
		Vector worldScale;
		std::string name = "";
		void SetParentObject(Group *parentObject){this->parentObject = parentObject;}
		Group *GetParentObject(){ return this->parentObject; }
		virtual double GetOrgWidth() { return this->width; }
		virtual double GetOrgHeight() { return this->height; }
		int GetOpacity() { return this->opacity; }
		void SetOpacityAffectByParent(bool opacityAffectByParent) { this->opacityAffectByParent = opacityAffectByParent; }
		bool IsOpacityAffectByParent() {return this->opacityAffectByParent;}
		void SetOpacity(int opacity) { if (opacity > 255) { this->opacity = 255; } else this->opacity = opacity; }
		Tag tag = 0;
		Rect GetRect(bool isGetWorldRect = false);
	protected:
		Game *game;
		bool opacityAffectByParent = true;
		int opacity = 255;
		Group* parentObject = nullptr;
		double width;
		double height;
		Vector anchor;
		Vector scale;
		bool visible;
		double rotate;
		DrawManager *drawManager;
		LPD3DXSPRITE spriteHandle;
	};
}