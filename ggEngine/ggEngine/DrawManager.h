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
		float fX;
		float fY;
		float fZ;
		float fRHW;
		D3DCOLOR Color;
		float fU;
		float fV;
	};
	class State;
	class Group;
	class Sprite;
	class Texture;
	class Game;
	class StateManager;
	class DrawObject;
	class Camera;
	class Shape;
	class DrawManager:public GGObject{
	public:
		DrawManager(Game *game, Camera* camera);
		~DrawManager();
		void Destroy();
		void Render2D();
		void DrawRectangle(float left, float top, float right, float bottom, D3DCOLOR fillColor = DEFAULT_COLOR);
		void DrawCircle(float x, float y, float radius, D3DCOLOR fillCOlor = DEFAULT_COLOR);
		void DrawObjectFromGroup(std::list<Group*> groupList);
		void DrawList(std::list<DrawObject*> *drawObjectList);
		void DrawLine(const Vector Point1, const Vector Point2, D3DCOLOR color = DEFAULT_COLOR);
		Sprite* CreateSprite(std::string fileSource);
		void DrawShape(Shape *shape);
		IDirect3DDevice9 *GetDevice(){ return this->device; }
		D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V);
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
	};
}