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
		Animator* Reset();
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
		Animator* SetOnBegin(std::function<void(Animator* animator)> onAnimatorBegin);
		Animator* SetOnCompleted(std::function<void(Animator* animator)> onAnimatorComplete);
	private:
		std::function<void(Animator* animator)> onAnimatorBegin;
		std::function<void(Animator* animator)> onAnimatorCompleted;
		std::string name;
		RECT *frameList;
		bool isBegin = false;
	};
}