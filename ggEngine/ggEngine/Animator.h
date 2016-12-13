#pragma once
#include <d3d9.h>
#include "SpriteAnimation.h"
#include "GGObject.h"
#include <vector>
#include <functional>
namespace ggEngine {
	class Animator:public GGObject {
	public:
		Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation, std::string name, bool isLoop);
		Animator(std::vector<int> frameList, SpriteAnimation *spriteAnimation, std::string name, bool isLoop);
		virtual ~Animator();
		Animator* Reset();
		int GetNextFrameIndex(bool forceGetNextFrame = false);
		bool isFinished;
		int frameWidth;
		int frameHeight;
		int currentFrame;
		int currentIndex;
		int endIndex;
		bool isLoop;
		int framePerRow;
		int framePerColumn;
		SpriteAnimation* spriteAnimation = nullptr;
		Animator* SetOnBegin(std::function<void(Animator* animator)> onAnimatorBegin);
		Animator* SetOnCompleted(std::function<void(Animator* animator)> onAnimatorComplete);
		std::vector<int> frameList;
		std::string name;
	private:
		void SetFrameIndex(int index);
		void Init(SpriteAnimation *spriteAnimation, std::string name, bool isLoop);
		std::function<void(Animator* animator)> onAnimatorBegin;
		std::function<void(Animator* animator)> onAnimatorCompleted;
		bool isBegin = false;
	};
}