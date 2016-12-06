#pragma once
#include "Sprite.h"
#include <map>
#include "StaticTimer.h"
namespace ggEngine {
	enum SpriteAnimationType { SA_RectangleSheet, SA_XMLSheet };
	class Animator;
	class Game;
	class SpriteAnimation : public Sprite {
	public:
		SpriteAnimation(Game *game, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
		virtual ~SpriteAnimation();
		void Draw() override;
		void DrawRect() override;
		void CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop = true);
		Animator* PlayAnimation(std::string animationName);
		void ResetAnimation(std::string animationName);
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
		virtual double GetOrgWidth() { return this->frameWidth; }
		virtual double GetOrgHeight() { return this->frameHeight; }
	private:
		///Deprecated
		void NextAnimationFrame(std::string animationName);
		std::string nextAnimationName = "";
		int GetNextFrameIndex();
		StaticTimer animationTimer;
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
		Animator *currentAnimation = nullptr;
		int numberOfFrame;
		DWORD msPerFrame;
		std::map<std::string, Animator*> animatorMap;
		SpriteAnimationType spriteAnimationType;
	};
}