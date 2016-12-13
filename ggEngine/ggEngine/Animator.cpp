#include "Animator.h"
namespace ggEngine {
	Animator::Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation,std::string name, bool isLoop)
	{
		this->name = name;

		Init(spriteAnimation, name, isLoop);

		this->frameList.reserve(endFrame - startFrame + 1);
		for (int i = startFrame; i <= endFrame; i++) {
			this->frameList.push_back(i);
		}
		endIndex = this->frameList.size() - 1;
		SetFrameIndex(0);
	}
	Animator::Animator(std::vector<int> frameList, SpriteAnimation * spriteAnimation, std::string name, bool isLoop)
	{
		Init(spriteAnimation, name, isLoop);
		this->frameList = frameList;
		endIndex = this->frameList.size() - 1;
		SetFrameIndex(0);
	}
	Animator::~Animator()
	{
	}

	Animator* Animator::Reset()
	{
		SetFrameIndex(0);
		this->isFinished = false;
		return this;
	}
	int Animator::GetNextFrameIndex(bool forceGetNextFrame)
	{
		if (forceGetNextFrame) {
			SetFrameIndex(++this->currentIndex);
			if (this->currentIndex > this->endIndex) SetFrameIndex(0);
			return currentFrame;
		}
		int nextFrame = this->currentFrame;
		if (!isBegin) {
			isBegin = true;
			if (this->onAnimatorBegin != nullptr) {
				this->onAnimatorBegin(this);
			}
		}
		SetFrameIndex(++this->currentIndex);
		
		return nextFrame;
		
	}
	Animator * Animator::SetOnBegin(std::function<void(Animator*animator)> onAnimatorBegin)
	{
		this->onAnimatorBegin = onAnimatorBegin;
		return this;
	}
	Animator * Animator::SetOnCompleted(std::function<void(Animator*animator)> onAnimatorComplete)
	{
		this->onAnimatorCompleted = onAnimatorComplete;
		return this;
	}
	void Animator::SetFrameIndex(int index)
	{
		this->currentIndex = index;
		if (this->currentIndex > this->endIndex) {
			if (this->isLoop) {
				currentIndex = 0;
			}
			else {
				currentIndex = 0;
				this->isFinished = true;
				if (this->onAnimatorCompleted != nullptr) {
					this->onAnimatorCompleted(this);
				}
			}
		}
		this->currentFrame = this->frameList[this->currentIndex];
	}
	void Animator::Init(SpriteAnimation * spriteAnimation, std::string name, bool isLoop)
	{
		this->frameHeight = spriteAnimation->GetFrameHeight();
		this->frameWidth = spriteAnimation->GetFrameWidth();
		this->framePerColumn = spriteAnimation->GetFramePerColumn();
		this->framePerRow = spriteAnimation->GetFramePerRow();
		this->isLoop = isLoop;
		this->isFinished = false;
		this->spriteAnimation = spriteAnimation;
	}
}
