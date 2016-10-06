#include "DrawManager.h"
#include "Group.h"
#include "Sprite.h"
#include "Texture.h"
#include "Game.h"
#include "State.h"
#include "StateManager.h"
#include "Camera.h"
#include "Circle.h"
#include "Rectangle.h"
namespace ggEngine {
	Sprite* DrawManager::CreateSprite(std::string fileSource){
		return new Sprite(this, fileSource);
	}
	DrawManager::DrawManager(Game * game, Camera * camera)
	{
		this->stateManager = game->stateManager;
		this->device = &game->GetD3DManager()->getDevice();
		this->camera = camera;
		D3DXCreateLine(this->device, &this->lineManager);
		this->device->CreateOffscreenPlainSurface(
			100,
			100,
			D3DFMT_X8R8G8B8,
			D3DPOOL_DEFAULT,
			&colorSurface,
			NULL);
		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}
	}
	DrawManager::~DrawManager()
	{
		if (this->lineManager != NULL) {
			this->lineManager->Release();
		}
	}

	void DrawManager::Destroy()
	{
		
	}

	void DrawManager::Render2D()
	{
		Update2D();
	}

	void DrawManager::DrawRectangleToWorld(float left, float top, float right, float bottom, D3DCOLOR fillColor)
	{
		device->ColorFill(colorSurface, NULL, fillColor);
		RECT rect = { left, top, right, bottom };
		device->StretchRect(
			colorSurface,			// from 
			NULL,				// which portion?
			backBuffer,			// to 
			&rect,				// which portion?
			D3DTEXF_NONE);
	}
	void DrawManager::DrawRectangle(float left, float top, float right, float bottom,D3DCOLOR fillColor)
	{
		device->ColorFill(colorSurface, NULL, fillColor);
		Vector leftTop = Vector(left, top);
		Vector rightBottom = Vector(right, bottom);
		leftTop.TransformCord(camera->GetTranslatedMatrix());
		rightBottom.TransformCord(camera->GetTranslatedMatrix());
		RECT rect = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
		device->StretchRect(
			colorSurface,			// from 
			NULL,				// which portion?
			backBuffer,			// to 
			&rect,				// which portion?
			D3DTEXF_NONE);
	}
	void DrawManager::DrawShape(Shape* shape){
		Rectangle *rect = dynamic_cast<Rectangle*>(shape);
		if (rect != NULL) {
			int width = rect->p3.x-rect->p1.x;
			int height = rect->p3.y-rect->p1.y;
			DrawLine(rect->p1, Vector(rect->p1.x+ width,rect->p1.y));
			DrawLine(Vector(rect->p1.x + width, rect->p1.y), rect->p3);
			DrawLine(rect->p3, Vector(rect->p1.x, rect->p1.y + height));
			DrawLine(Vector(rect->p1.x, rect->p1.y + height), rect->p1);
		}
		else {
			Circle *circle = dynamic_cast<Circle*>(shape);
			DrawCircle(circle->pCenter.x, circle->pCenter.y, circle->radius);
		}
	}
	void DrawManager::DrawCircle(float x, float y, float radius, D3DCOLOR fillCOlor)
	{
		const int NUMPOINTS = 24;

		const float PI = 3.14159;
		Vector pt = Vector(x, y);
		D3DTLVERTEX Circle[NUMPOINTS + 1];
		int i;
		float X;
		float Y;
		float Theta; //Size of angle between two points on the circle (single wedge)
		float WedgeAngle;	

		//Precompute WedgeAngle

		WedgeAngle = (float)((2 * PI) / NUMPOINTS);
		//Set up vertices for a circle

		//Used <= in the for statement to ensure last point meets first point (closed circle)

		for (i = 0; i <= NUMPOINTS; i++)
		{
			//Calculate theta for this vertex
			Theta = i * WedgeAngle;
			//Compute X and Y locations
			X = (float)(pt.x + radius * cos(Theta));
			Y = (float)(pt.y - radius * sin(Theta));
			Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, fillCOlor, 0.0f, 0.0f);
		}
		//Now draw the circle
		device->SetFVF(D3DFVF_TL);
		device->SetTexture(0, NULL);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));

	}
	void DrawManager::DrawLine(const Vector v1, const Vector v2, D3DCOLOR color)
	{
		D3DTLVERTEX line[2];
		line[0] = CreateD3DTLVERTEX(v1.x, v1.y, 0.0f, 1.0f, color, 0.0f, 0.0f);
		line[1] = CreateD3DTLVERTEX(v2.x, v2.y, 0.0f, 1.0f, color, 0.0f, 0.0f);
		device->SetFVF(D3DFVF_TL);
		device->SetTexture(0, NULL);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, 2, &line[0], sizeof(line[0]));
	}
	void DrawManager::DrawObjectFromGroup(std::list<Group*> *groupList)
	{
		for (std::list<Group*>::iterator it = groupList->begin(); it != groupList->end(); ++it) {
			if ((*it)->IsVisible()) {
				(*it)->UpdateWorldPosition();
				DrawList((*it)->GetDrawList());
				DrawObjectFromGroup((*it)->GetGroupList());
			}
		}
	}

	void DrawManager::DrawList(std::list<DrawObject*> *drawObjectList)
	{
		for (std::list<DrawObject*>::iterator it = drawObjectList->begin(); it != drawObjectList->end();) {
			if ((*it)->IsAlive()) {
				(*it)->UpdateWorldPosition();
				(*it)->Draw(camera->GetTranslatedMatrix());
				++it;
			}
			else {
				std::list<DrawObject*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				drawObjectList->erase(tempIt);
			}
		}
	}


	void DrawManager::Update2D()
	{
		State* state = this->stateManager->GetCurrentState();
		state->PreRender();
		DrawObjectFromGroup(state->GetGroupList());
		DrawObjectFromGroup(&this->topGroupList);
	}
	D3DTLVERTEX DrawManager::CreateD3DTLVERTEX(float X, float Y, float Z, float RHW,
		D3DCOLOR color, float U, float V)
	{
		D3DTLVERTEX v;

		v.fX = X;
		v.fY = Y;
		v.fZ = Z;
		v.fRHW = RHW;
		v.Color = color;
		v.fU = U;
		v.fV = V;

		return v;
	}
}