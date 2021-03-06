#include "Camera.h"
#include "Game.h"
#include "Input.h"
#include "GameObject.h"
namespace ggEngine {
	Camera::Camera(Game * game, int width, int height, double x , double y , bool enableManualMove)
	{
		this->game = game;
		this->device = &game->GetD3DManager()->getDevice();
		this->width = width;
		this->height = height;
		this->orgWidth = width;
		this->orgHeight = height;
		SetUpKeyControl();
		if (enableManualMove) EnableManualMove();
		SetPoint(width/2, height/2);
		SetScale(1, 1);
		this->rotate = 0;
		D3DXMatrixOrthoLH(&this->orthographicMatrix,width,-height,0.0f,1.0f);
		D3DXMatrixIdentity(&this->identityMatrix);
	}
	Camera::~Camera()
	{
	}
	void Camera::Draw()
	{
		Matrix tranMat;
		//tranMat = Matrix::CreateTranslateMatrix(-width / 2 - (this->point.x-width/2)*scale.x, -height / 2 - (this->point.y-height/2)*scale.x);
		////tranMat = Matrix::CreateTranslateMatrix(point.x-width / 2, point.y-height / 2);
		////tranMat *= Matrix::CreateTranslateMatrix(-(point.x - width / 2), -(point.y - height / 2));
		tranMat = Matrix::CreateScaleMatrix(this->scale.x, this->scale.y);
		//tranMat *= Matrix::CreateTranslateMatrix(width / 2 + (this->point.x - width / 2)*scale.x, height / 2 + (this->point.y - height / 2)*scale.x);
		////tranMat *= Matrix::CreateTranslateMatrix(-(width-orgWidth)/2,-(height-orgHeight)/2);
		tranMat *= Matrix::CreateTranslateMatrix(-this->point.x*scale.x, -this->point.y*scale.y);

		tranMat *= Matrix::CreateRotateMatrix(this->rotate);

		this->viewMatrix = tranMat;
		/*this->viewMatrix = D3DXMATRIX(
			scale.x*cos(rotate), scale.y*sin(rotate), 0, 0,
			-scale.y*sin(rotate), scale.y*cos(rotate), 0, 0,
			0, 0, 1, 0,
			-point.x*scale.x*cos(rotate) + point.y*scale.y*sin(rotate), -point.x*scale.y*sin(rotate) - point.y*scale.y*cos(rotate), 0, 1);
	*/	this->device->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
		this->device->SetTransform(D3DTS_WORLD, &identityMatrix);
		this->device->SetTransform(D3DTS_VIEW, &viewMatrix);
		
	}
	void Camera::Update()
	{
		switch (this->followType)
		{
		case CameraFollowType::Normal:
			point = this->follow->worldPosition;
			return;
		case CameraFollowType::XOnly:
			point.x = this->follow->worldPosition.x;
			return;
		default:
			break;
		}
		if (this->enableManualMove) {
			if (game->GetInput()->KeyDown(controlKey[CameraControl_ZoomIn])) {
				scale.x += SCALE_SPEED*scale.x;
				scale.y += SCALE_SPEED*scale.y;
				this->width = orgWidth/scale.x;
				this->height = orgHeight/scale.y;
			}
			if (game->GetInput()->KeyDown(controlKey[CameraControl_ZoomOut])) {
				if (!(scale.x < 0 || scale.y < 0)) {
					scale.x -= SCALE_SPEED*scale.x;
					scale.y -= SCALE_SPEED*scale.y;
					this->width = orgWidth/scale.x;
					this->height = orgHeight/scale.y;
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
	}
	void Camera::SetScale(double x, double y)
	{
		this->scale = Vector(x, y);
		this->width = orgWidth/x;
		this->height = orgHeight/y;
	}
	void Camera::SetPoint(double x, double y)
	{
		this->point = Vector(x, y);
	}
	void Camera::SetPoint(Vector position)
	{
		this->point = position;
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
		rotate = 0;
		point = Vector(width/2, height/2);
	}
	void Camera::Follow(GameObject * go)
	{
		this->enableManualMove = false;
		this->follow = go;
		this->followType = CameraFollowType::Normal;
	}
	void Camera::FollowX(GameObject * go)
	{
		this->enableManualMove = false;
		this->follow = go;
		this->followType = CameraFollowType::XOnly;
	}
	void Camera::UnFollow()
	{
		this->enableManualMove = true;
		this->follow = nullptr;
		this->followType = CameraFollowType::None;
	}
	RECT Camera::GetRect()
	{
		return{ (long)(point.x - width / 2) ,(long)(point.y - height / 2),(long)(point.x + width / 2),(long)(point.y + height / 2) };
	}
	Rect Camera::GetNormalRect()
	{
		Rect r(point.x - width / 2, point.y - height / 2, point.x + width / 2, point.y + height / 2);
		return r;
	}
	void Camera::SetWidth(double width)
	{
		this->scale.x =  orgWidth / width;
		this->width = width;
	}
	void Camera::SetHeight(double height)
	{
		this->scale.y =  orgHeight/height;
		this->height = height;
	}
	void Camera::SetOrgWidth(double width)
	{
		this->orgWidth = width;
		this->width = width;
		this->scale.x = 1;
	}
	void Camera::SetOrgHeight(double height)
	{
		this->orgHeight = height;
		this->height = height;
		this->scale.y = 1;
	}
	void Camera::SetMask(Rect rect)
	{
		this->mask = rect;
	}
	Rect Camera::GetMask()
	{
		return this->mask;
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
		controlKey[CameraControl_ManualMove] = DIK_DIVIDE;

	}
}
