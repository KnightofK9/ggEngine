#include "Animator.h"
namespace ggEngine {
	Animator::Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation, bool isLoop)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame; 
		this->frameHeight = spriteAnimation->GetFrameHeight();
		this->frameWidth = spriteAnimation->GetFrameWidth();
		this->framePerColumn = spriteAnimation->GetFramePerColumn();
		this->framePerRow = spriteAnimation->GetFramePerRow();
		this->isLoop = isLoop;
		this->currentFrame = startFrame;
		this->isFinished = false;
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
	RECT Animator::GetNextRect()
	{
		if (isFinished) {
			return RECT();
		}
		int currentFrameRow = ((this->currentFrame) / this->framePerRow);
		int currentFrameColumn = (this->currentFrame - ((currentFrameRow)*this->framePerRow));
		int top = this->frameHeight*currentFrameRow;
		int left = this->frameWidth*currentFrameColumn;
		int right = left + this->frameWidth;
		int bottom = top + this->frameHeight;
		this->srcRect = { left,top,right,bottom };
		this->currentFrame++;
		if (this->currentFrame > this->endFrame) {
			if (this->isLoop) {
				this->currentFrame = this->startFrame;
			}
			else {
				this->isFinished = true;
			}
		}
		return this->srcRect;
	}
}
