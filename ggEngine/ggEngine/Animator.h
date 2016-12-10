#pragma once
#include <d3d9.h>
#include "SpriteAnimation.h"
#include "GGObject.h"
#include <functional>
namespace ggEngine {
	class Animator:public GGObject {
	public:
		Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation, std::string name, bool isLoop);
		virtual ~Animator();
		void Reset();
		int GetNextFrameIndex(bool forceGetNextFrame = false);
		bool isFinished;
		int frameWidth;
		int frameHeight;
		int currentFrame;
		int startFrame;
		int endFrame;
		bool isLoop;
		int framePerRow;
		int framePerColumn;
		SpriteAnimation* spriteAnimation = nullptr;
		void SetOnBegin(std::function<void(Animator* animator)> onAnimatorBegin) { this->onAnimatorBegin = onAnimatorBegin; }
		void SetOnCompleted(std::function<void(Animator* animator)> onAnimatorComplete) { this->onAnimatorCompleted = onAnimatorCompleted; }
	private:
		std::function<void(Animator* animator)> onAnimatorBegin;
		std::function<void(Animator* animator)> onAnimatorCompleted;
		std::string name;
		RECT *frameList;
		bool isBegin = false;
	};
}