#include "Animator.h"
namespace ggEngine {
	Animator::Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation,std::string name, bool isLoop)
	{
		this->name = name;
		this->startFrame = startFrame;
		this->endFrame = endFrame; 
		this->frameHeight = spriteAnimation->GetFrameHeight();
		this->frameWidth = spriteAnimation->GetFrameWidth();
		this->framePerColumn = spriteAnimation->GetFramePerColumn();
		this->framePerRow = spriteAnimation->GetFramePerRow();
		this->isLoop = isLoop;
		this->currentFrame = startFrame;
		this->isFinished = false;
		this->spriteAnimation = spriteAnimation;
	}
	Animator::~Animator()
	{
	}
	void Animator::Destroy()
	{
	}
	void Animator::Reset()
	{
		this->currentFrame = this->startFrame;
		this->isFinished = false;
	}
	int Animator::GetNextFrameIndex(bool forceGetNextFrame)
	{
		if (forceGetNextFrame) {
			this->currentFrame++;
			if (this->currentFrame > this->endFrame) this->currentFrame = this->startFrame;
			return currentFrame;
		}
		if (isFinished) {
			return startFrame;
		}
		this->currentFrame++;
		if (this->currentFrame > this->endFrame) {
			if (this->isLoop) {
				this->currentFrame = this->startFrame;
			}
			else {
				this->isFinished = true;
				if (this->spriteAnimation->events->onAnimationCompleted != nullptr) {
					AnimationArg e;
					e.animator = this;
					e.animationName = this->name;
					this->spriteAnimation->events->onAnimationCompleted(this->spriteAnimation, e);
				}
			}
		}
		return currentFrame;
	}
}
