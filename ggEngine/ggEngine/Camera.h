#pragma once
#include "GGObject.h"
#include "Vector.h"
#include "Matrix.h"
namespace ggEngine {
	enum CameraControl {CameraControl_ZoomIn = 0, CameraControl_ZoomOut, CameraControl_MoveLeft, CameraControl_MoveRight, CameraControl_MoveUp, CameraControl_MoveDown};
	class Game;
	class Camera : public GGObject {
	public:
		Camera(Game *game, int width, int height,float x = 0, float y = 0, bool enableManualMove = false);
		~Camera();
		void Transform();
		void Update();
		void Destroy();
		void SetScale(float x, float y);
		void SetPoint(float x, float y);
		Matrix GetTranslatedMatrix() { return this->translatedMatrix; }
		void RegisterControl(CameraControl controlKeyCode, DWORD key);
		void EnableManualMove();
		void DisableManualMove();
	private:
		void SetUpKeyControl();
		bool enableManualMove;
		Vector point;
		Vector scale;
		Matrix translatedMatrix;
		Game *game;
		DWORD controlKey[6];
		float width;
		float height;
		float orgWidth;
		float  orgHeight;
		const float SCALE_SPEED = 0.01f;
		const float MOVE_SPEED = 25.0f;
	};
}