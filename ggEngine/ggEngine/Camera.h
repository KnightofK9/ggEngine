#pragma once
#include "GGObject.h"
#include "Vector.h"
#include "Matrix.h"
namespace ggEngine {
	class Game;
	class Camera : public GGObject {
	public:
		Camera(Game *game, int width, int height,float x = 0, float y = 0);
		~Camera();
		void Destroy();
		void SetPoint(float x, float y);
		Matrix GetTranslatedMatrix() { return this->translatedMatrix; }
	private:
		Vector point;
		Matrix translatedMatrix;
		Game *game;
		int width;
		int height;
	};
}