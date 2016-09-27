#include "Camera.h"
#include "Game.h"
namespace ggEngine {
	Camera::Camera(Game * game, int width, int height, float x , float y )
	{
		this->game = game;
		this->width = width;
		this->height = height;
		SetPoint(x, y);
	}
	Camera::~Camera()
	{
		if (this->point != NULL) delete point;
		if (this->translatedMatrix != NULL)delete translatedMatrix;
	}
	void Camera::Destroy()
	{
	}
	void Camera::SetPoint(float x, float y)
	{
		this->point = Vector(x, y);
		Matrix tranMat = Matrix::CreateTranslateMatrix(this->point.x, this->point.y);
		Matrix flipMat = Matrix::CreateScaleMatrix(1,-1);
		Matrix upTranMat = Matrix::CreateTranslateMatrix(0, height);
		this->translatedMatrix = tranMat*flipMat*upTranMat;
	}
}
