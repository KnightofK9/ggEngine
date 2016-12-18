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
#include "World.h"
namespace ggEngine {
	DrawManager::DrawManager(Game * game, Camera * camera)
	{
		this->game = game;
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


	void DrawManager::Update(double dt)
	{
		Render2D();
	}

	void DrawManager::Reset()
	{
	}

	void DrawManager::Render2D()
	{
		Update2D();
		camera->Update();
		camera->Draw();
	}

	void DrawManager::DrawRectangleToWorld(double left, double top, double right, double bottom, D3DCOLOR fillColor)
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
	void DrawManager::DrawRectangle(double left, double top, double right, double bottom,D3DCOLOR fillColor)
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
			Vector p1 = rect->p1;
			Vector p3 = rect->p3;
			Vector translated = this->camera->GetPoint() - Vector(this->camera->GetWidth()/2,this->camera->GetHeight()/2);
			p1 -= translated;
			p3 -= translated;
			DrawLine(p1, Vector(p1.x+ width,p1.y));
			DrawLine(Vector(p1.x + width,p1.y),p3);
			DrawLine(p3, Vector(p1.x, p1.y + height));
			DrawLine(Vector(p1.x, p1.y + height),p1);
		}
		else {
			Circle *circle = dynamic_cast<Circle*>(shape);
			DrawCircle(circle->pCenter.x, circle->pCenter.y, circle->radius);
		}
	}
	void DrawManager::DrawCircle(double x, double y, double radius, D3DCOLOR fillCOlor)
	{
		const int NUMPOINTS = 24;

		const double PI = 3.14159;
		Vector pt = Vector(x, y);
		D3DTLVERTEX Circle[NUMPOINTS + 1];
		int i;
		double X;
		double Y;
		double Theta; //Size of angle between two points on the circle (single wedge)
		double WedgeAngle;	

		//Precompute WedgeAngle

		WedgeAngle = (double)((2 * PI) / NUMPOINTS);
		//Set up vertices for a circle

		//Used <= in the for statement to ensure last point meets first point (closed circle)

		for (i = 0; i <= NUMPOINTS; i++)
		{
			//Calculate theta for this vertex
			Theta = i * WedgeAngle;
			//Compute X and Y locations
			X = (double)(pt.x + radius * cos(Theta));
			Y = (double)(pt.y - radius * sin(Theta));
			Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, fillCOlor, 0.0f, 0.0f);
		}
		//Now draw the circle
		device->SetFVF(D3DFVF_TL);
		device->SetTexture(0, NULL);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));

	}
	void DrawManager::DrawLine(const Vector v1, const Vector v2,int width, D3DCOLOR color)
	{
		D3DXVECTOR2 vLine[2];
		lineManager->SetWidth(width);
		lineManager->SetAntialias(false);
		lineManager->SetGLLines(true);
		vLine[0].x = v1.x;
		vLine[0].y = v1.y;
		vLine[1].x = v2.x;
		vLine[1].y = v2.y;
		lineManager->Begin();
		lineManager->Draw(vLine, 2, color);
		lineManager->End();

		/*D3DTLVERTEX line[2];
		line[0] = CreateD3DTLVERTEX(v1.x, v1.y, 0.0f, 1.0f, color, 0.0f, 0.0f);
		line[1] = CreateD3DTLVERTEX(v2.x, v2.y, 0.0f, 1.0f, color, 0.0f, 0.0f);
		device->SetFVF(D3DFVF_TL);
		device->SetTexture(0, NULL);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, 2, &line[0], sizeof(line[0]));*/
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

	void DrawManager::DrawList(std::list<GameObject*> drawObjectList,bool drawMask)
	{
		for (std::list<GameObject*>::iterator it = drawObjectList.begin(); it != drawObjectList.end();++it) {
			if ((*it)->IsAlive()) {
				(*it)->UpdateWorldPosition();
				if (drawMask) {
					(*it)->DrawRect();
				}
				else (*it)->Draw();
			}
			/*else {
				std::list<GameObject*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				drawObjectList->erase(tempIt);
			}*/
		}
	}


	void DrawManager::Update2D()
	{
		/*State* state = this->stateManager->GetCurrentState();
		state->PreRender();*/
		//DrawObjectFromGroup(game->world->GetGroupList());
		game->world->Draw();
		//DrawObjectFromGroup(&this->topGroupList);
	}
	D3DTLVERTEX DrawManager::CreateD3DTLVERTEX(double X, double Y, double Z, double RHW,
		D3DCOLOR color, double U, double V)
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
	void DrawManager::ChangeRenderTargetTo(Texture * texture)
	{
		LPDIRECT3DSURFACE9 surfaceTexture = texture->GetSurfaceTexture();
		device->SetRenderTarget(0, surfaceTexture);
		device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	}
	void DrawManager::ResetRenderTarget()
	{
		device->SetRenderTarget(0, backBuffer);
	}
}