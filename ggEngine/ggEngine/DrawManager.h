#pragma once
#include "GGObject.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "ConstantEnum.h"
#include <map>
#include <list>
namespace ggEngine {
	struct D3DTLVERTEX
	{
		double fX;
		double fY;
		double fZ;
		double fRHW;
		D3DCOLOR Color;
		double fU;
		double fV;
	};
	class State;
	class Group;
	class Sprite;
	class Texture;
	class Game;
	class StateManager;
	class GameObject;
	class Camera;
	class Shape;
	class DrawManager:public GGObject{
	public:
		DrawManager(Game *game, Camera* camera);
		~DrawManager();
		void Destroy();
		void Render2D();
		void DrawRectangleToWorld(double left, double top, double right, double bottom, D3DCOLOR fillColor = DEFAULT_COLOR);
		void DrawRectangle(double left, double top, double right, double bottom, D3DCOLOR fillColor = DEFAULT_COLOR);
		void DrawCircle(double x, double y, double radius, D3DCOLOR fillCOlor = DEFAULT_COLOR);
		void DrawObjectFromGroup(std::list<Group*> *groupList);
		void DrawList(std::list<GameObject*> *drawObjectList);
		void DrawLine(const Vector Point1, const Vector Point2, D3DCOLOR color = DEFAULT_COLOR);
		void DrawShape(Shape *shape);
		IDirect3DDevice9 *GetDevice(){ return this->device; }
		D3DTLVERTEX CreateD3DTLVERTEX(double X, double Y, double Z, double RHW, D3DCOLOR color, double U, double V);
		LPD3DXSPRITE GetSpriteHandle(){ return this->spriteHandle; }
		LPDIRECT3DSURFACE9 GetColorSurface(){ return this->colorSurface; }
	private:
		LPD3DXSPRITE spriteHandle;
		LPDIRECT3DSURFACE9 colorSurface;
		LPDIRECT3DSURFACE9 backBuffer;
		LPD3DXLINE lineManager;
		Camera *camera;
		void Update2D();
		IDirect3DDevice9 *device;
		StateManager *stateManager;
		std::list<Group*> topGroupList;
		Game *game;
	};
}