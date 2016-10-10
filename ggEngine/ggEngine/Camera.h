#pragma once
#include "GGObject.h"
#include "Vector.h"
#include "Matrix.h"
namespace ggEngine {
	enum CameraControl {CameraControl_ZoomIn = 0, CameraControl_ZoomOut, CameraControl_Reset, CameraControl_MoveLeft, CameraControl_MoveRight, CameraControl_MoveUp, CameraControl_MoveDown};
	class Game;
	class Camera : public GGObject {
	public:
		Camera(Game *game, int width, int height,double x = 0, double y = 0, bool enableManualMove = false);
		~Camera();
		void Transform();
		void Update();
		void Destroy();
		void SetScale(double x, double y);
		void SetPoint(double x, double y);
		Matrix GetTranslatedMatrix() { return this->translatedMatrix; }
		void RegisterControl(CameraControl controlKeyCode, DWORD key);
		void EnableManualMove();
		void DisableManualMove();
		void ResetView();
	private:
		void SetUpKeyControl();
		bool enableManualMove;
		Vector point;
		Vector scale;
		Matrix translatedMatrix;
		Game *game;
		DWORD controlKey[7];
		double width;
		double height;
		double orgWidth;
		double  orgHeight;
		const double SCALE_SPEED = 0.01f;
		const double MOVE_SPEED = 25.0f;
	};
}