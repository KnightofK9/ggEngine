#pragma once
#include "GGObject.h"
#include "Vector.h"
#include "Matrix.h"
#include <d3d9.h>
#include "Rect.h"
namespace ggEngine {
	enum CameraControl {CameraControl_ZoomIn = 0, CameraControl_ZoomOut, CameraControl_RotateRight, CameraControl_RotateLeft, CameraControl_Reset, CameraControl_MoveLeft, CameraControl_MoveRight, CameraControl_MoveUp, CameraControl_MoveDown,CameraControl_ManualMove};
	class Game;
	class GameObject;
	enum CameraFollowType { XOnly,YOnly, Normal, None};
	class Camera : public GGObject {
	public:
		Camera(Game *game, int width, int height,double x = 0, double y = 0, bool enableManualMove = false);
		virtual ~Camera();
		void Draw();
		virtual void Update();
		void SetScale(double x, double y);
		void SetPoint(double x, double y);
		Vector GetPoint() { return this->point; }
		void SetPoint(Vector position);
		Matrix GetTranslatedMatrix() { return this->viewMatrix; }
		void RegisterControl(CameraControl controlKeyCode, DWORD key);
		void EnableManualMove();
		void DisableManualMove();
		void ResetView();
		void Follow(GameObject *go);
		void FollowX(GameObject *go);
		void UnFollow();
		RECT GetRect();
		virtual Rect GetNormalRect();
		void SetWidth(double width);
		void SetHeight(double height);
		double GetWidth() { return this->width; }
		double GetHeight() { return this->height; }
		void SetOrgWidth(double width);
		void SetOrgHeight(double height);
		void SetMask(Rect rect);
		Rect GetMask();
		Vector GetScale() { return this->scale; }
		Vector point;
	protected:
		GameObject *follow = nullptr;
		CameraFollowType followType = CameraFollowType::None;
		LPDIRECT3DDEVICE9 device;
		void SetUpKeyControl();
		bool enableManualMove;
		double rotate;
		Vector scale;
		Rect mask;
		Matrix translatedMatrix;
		Game *game;
		DWORD controlKey[10];
		double width;
		double height;
		double orgWidth;
		double  orgHeight;
		const double SCALE_SPEED = 0.01f;
		const double MOVE_SPEED = 25.0f;
		const double ROTATE_SPEED = 3.14 / 60;
		D3DXMATRIX orthographicMatrix;
		D3DXMATRIX identityMatrix;
		D3DXMATRIX viewMatrix;
	};
}