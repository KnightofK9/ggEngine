#include "Camera.h"
#include "Game.h"
#include "Input.h"
namespace ggEngine {
	Camera::Camera(Game * game, int width, int height, double x , double y , bool enableManualMove)
	{
		this->game = game;
		this->width = width;
		this->height = height;
		this->orgWidth = width;
		this->orgHeight = height;
		SetUpKeyControl();
		if (enableManualMove) EnableManualMove();
		SetPoint(x, y);
		SetScale(1, 1);
		this->rotate = 0;
	}
	Camera::~Camera()
	{
	}
	void Camera::Transform()
	{
		Matrix tranMat;
		tranMat = Matrix::CreateTranslateMatrix(-width / 2, -height / 2);
		tranMat *= Matrix::CreateRotateMatrix(this->rotate);
		tranMat *= Matrix::CreateTranslateMatrix(width / 2, height / 2);
		tranMat *= Matrix::CreateScaleMatrix(this->scale.x, this->scale.y);
		tranMat *= Matrix::CreateTranslateMatrix(-(width-orgWidth)/2,-(height-orgHeight)/2);
		tranMat *= Matrix::CreateTranslateMatrix(-this->point.x*scale.x, -this->point.y*scale.y);
		this->translatedMatrix = tranMat;
	}
	void Camera::Update()
	{
		if (enableManualMove) {
			if (game->GetInput()->KeyDown(controlKey[CameraControl_ZoomIn])) {
				scale.x += SCALE_SPEED*scale.x;
				scale.y += SCALE_SPEED*scale.y;
				this->width = orgWidth*scale.x;
				this->height = orgHeight*scale.y;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_ZoomOut])) {
				if (!(scale.x < 0 || scale.y < 0)) {
					scale.x -= SCALE_SPEED*scale.x;
					scale.y -= SCALE_SPEED*scale.y;
					this->width = orgWidth*scale.x;
					this->height = orgHeight*scale.y;
				}
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_MoveLeft])) {
				point.x -= MOVE_SPEED/scale.x;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_MoveRight])) {
				point.x += MOVE_SPEED/scale.x;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_MoveUp])) {
				point.y -= MOVE_SPEED/scale.x;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_MoveDown])) {
				point.y += MOVE_SPEED/scale.x;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_Reset])) {
				ResetView();
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_RotateLeft])) {
				rotate -= ROTATE_SPEED;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_RotateRight])) {
				rotate += ROTATE_SPEED;
			}
		}
		Transform();
	}
	void Camera::Destroy()
	{
	}
	void Camera::SetScale(double x, double y)
	{
		this->scale = Vector(x, y);
		this->width = orgWidth*x;
		this->height = orgHeight*y;
	}
	void Camera::SetPoint(double x, double y)
	{
		this->point = Vector(x, y);
	}
	void Camera::RegisterControl(CameraControl controlKeyCode, DWORD key)
	{
		controlKey[controlKeyCode] = key;
	}
	void Camera::EnableManualMove()
	{
		this->enableManualMove = true;
	}
	void Camera::DisableManualMove()
	{
		this->enableManualMove = false;
	}
	void Camera::ResetView()
	{
		SetScale(1, 1);
		point = Vector(0, 0);
		rotate = 0;
	}
	void Camera::SetUpKeyControl()
	{
		controlKey[CameraControl_ZoomIn] = DIK_NUMPAD3;
		controlKey[CameraControl_ZoomOut] = DIK_NUMPAD1;
		controlKey[CameraControl_MoveLeft] = DIK_NUMPAD4;
		controlKey[CameraControl_MoveRight] = DIK_NUMPAD6;
		controlKey[CameraControl_MoveUp] = DIK_NUMPAD8;
		controlKey[CameraControl_MoveDown] = DIK_NUMPAD2;
		controlKey[CameraControl_Reset] = DIK_NUMPAD0;
		controlKey[CameraControl_RotateLeft] = DIK_NUMPAD7;
		controlKey[CameraControl_RotateRight] = DIK_NUMPAD9;
	}
}
