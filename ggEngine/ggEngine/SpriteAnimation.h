#pragma once
#include "Sprite.h"
#include <map>
namespace ggEngine {
	enum SpriteAnimationType { SA_RectangleSheet, SA_XMLSheet };
	class Animator;
	class SpriteAnimation : public Sprite {
	public:
		SpriteAnimation(DrawManager *drawManager, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0);
		~SpriteAnimation();
		void Draw(Matrix translatedWorldMatrix);
		void Destroy();
		void CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop = true);
		void NextAnimationFrame(std::string animationName);
		void PlayAnimation(std::string animationName);
		void SetImage(SpriteInfo *image, int frameWidth, int frameHeight, int numberOfFrame = 0);
		int GetNumberOfFrame() { return this->numberOfFrame; }
		void SetWidth(double width);
		void SetHeight(double height);
		void SetScale(double x, double y);
		double GetWidth();
		double GetHeight();
		int GetFrameWidth() { return this->frameWidth; }
		int GetFrameHeight() { return this->frameHeight; }
		int GetFramePerColumn() { return this->framePerColumn; }
		int GetFramePerRow() { return this->framePerRow; }
		void SetFrame(int frameIndex,bool isStopAnimation = true);
	private:
		void InitFrameList();
		void SetCurrentSrcRect();
		RECT *frameList = NULL;
		RECT srcRect;
		int framePerRow;
		int framePerColumn;
		int frameWidth;
		int frameHeight;
		int currentFrame;
		bool isRunningAnimation;
		Animator *currentAnimation = NULL;
		int numberOfFrame;
		std::map<std::string, Animator*> animatorMap;
		SpriteAnimationType spriteAnimationType;
	};
}