#pragma once
#include "Sprite.h"
#include <map>
namespace ggEngine {
	enum SpriteAnimationType { SA_RectangleSheet, SA_XMLSheet };
	class Animator;
	class SpriteAnimation : public Sprite {
	public:
		SpriteAnimation(LPDIRECT3DDEVICE9 device, Texture *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0);
		~SpriteAnimation();
		void Draw();
		void Destroy();
		void CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop = true);
		void PlayAnimation(std::string animationName);
		void SetImage(Texture *image, int frameWidth, int frameHeight, int numberOfFrame = 0);
		int GetNumberOfFrame() { return this->numberOfFrame; }
		void SetWidth(float width);
		void SetHeight(float height);
		float GetWidth();
		float GetHeight();
		int GetFrameWidth() { return this->frameWidth; }
		int GetFrameHeight() { return this->frameHeight; }
		int GetFramePerColumn() { return this->framePerColumn; }
		int GetFramePerRow() { return this->framePerRow; }
	private:
		int framePerRow;
		int framePerColumn;
		int frameWidth;
		int frameHeight;
		int currentFrame;
		bool isRunningAnimation;
		Animator *currentAnimation;
		int numberOfFrame;
		std::map<std::string, Animator*> animatorMap;
		SpriteAnimationType spriteAnimationType;
	};
}