#include "SpriteAnimation.h"
#include "Animator.h"
#include "Texture.h"
#include "Debug.h"
namespace ggEngine {
	SpriteAnimation::SpriteAnimation(DrawManager *drawManager, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame) :Sprite(drawManager)
	{
		this->spriteAnimationType = SA_RectangleSheet;
		this->currentFrame = defaultFrame;
		this->isRunningAnimation = false;
		SetImage(image, frameWidth, frameHeight, numberOfFrame);
		InitFrameList();
		srcRect = frameList[defaultFrame];
		SetAnchor(0.5, 0.5);
		//SetCurrentSrcRect();
	}
	SpriteAnimation::~SpriteAnimation()
	{
		for (std::map<std::string, Animator*>::iterator it = this->animatorMap.begin(); it != this->animatorMap.end(); ++it) {
			delete (it->second);
		};
		animatorMap.clear();
		//if(currentAnimation!=NULL) delete currentAnimation;
		if (frameList != NULL) delete frameList;
	}
	void SpriteAnimation::Draw(Matrix translatedWorldMatrix)
	{
		Transform(translatedWorldMatrix,spriteHandle);
		if (!visible) return;
		if (this->isRunningAnimation && this->currentAnimation->isFinished) this->isRunningAnimation = false;
		if (this->isRunningAnimation) {
			int frameIndex = this->currentAnimation->GetNextFrameIndex();
			srcRect = frameList[frameIndex];
		}
		else {
			
		}
		if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			color = (color & 0x00FFFFFF) | (opacity << 24);
			spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, NULL, color);
			spriteHandle->End();
		}
	}
	void SpriteAnimation::Destroy()
	{
		GameObject::Destroy();
	}
	void SpriteAnimation::CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop)
	{
		if (endFrame > this->numberOfFrame) {
			g_debug.Warning("End frame is bigger than number of frame.");
			endFrame = this->numberOfFrame;
		}
		if (startFrame < 0) {
			g_debug.Warning("Start frame must not be negative.");
			startFrame = 0;
		}
		animatorMap[animationName] = new Animator(startFrame, endFrame, this, isLoop);
	}
	void SpriteAnimation::NextAnimationFrame(std::string animationName)
	{
		std::map<std::string, Animator*>::iterator it = this->animatorMap.find(animationName);
		if (it != this->animatorMap.end())
		{
			if (this->currentAnimation == (it->second)) {
				this->srcRect = frameList[this->currentAnimation->GetNextFrameIndex(true)];
				return;
			}

			this->currentAnimation = (it->second);
			this->isRunningAnimation = false;
		}
		else {
			g_debug.Warning("No animation found  with key " + animationName);
		}
	}
	void SpriteAnimation::PlayAnimation(std::string animationName)
	{
		std::map<std::string, Animator*>::iterator it = this->animatorMap.find(animationName);
		if (it != this->animatorMap.end())
		{
			if (this->currentAnimation == (it->second) ){
				return;
			}
			this->currentAnimation = (it->second);
			this->isRunningAnimation = true;
		}
		else {
			g_debug.Warning("No animation found  with key " + animationName);
		}
	}
	void SpriteAnimation::SetImage(SpriteInfo * image, int frameWidth, int frameHeight, int numberOfFrame)
	{
		this->image = image;
		this->height = this->frameHeight = frameHeight;
		this->width = this->frameWidth = frameWidth;
		this->framePerRow = this->image->GetWidth() / frameWidth;
		this->framePerColumn = this->image->GetHeight() / frameHeight;
		int num = this->framePerRow*this->framePerColumn;
		if (num > numberOfFrame && numberOfFrame != 0) {
			this->numberOfFrame = numberOfFrame;
		}
		else {
			this->numberOfFrame = num;
		}
	}
	void SpriteAnimation::SetWidth(double width)
	{
		this->scale.x = ((double)width / this->frameWidth);
		this->width = width;
	}
	void SpriteAnimation::SetHeight(double height)
	{
		this->scale.y = (double)height / this->frameHeight;
		this->height = height;
	}
	void SpriteAnimation::SetScale(double x, double y)
	{
		GameObject::SetScale(x, y);
		this->width = this->frameWidth*x;
		this->height = this->frameHeight*y;
	}
	double SpriteAnimation::GetWidth()
	{
		//return this->frameWidth*this->scale.x;
		return this->width;
	}
	double SpriteAnimation::GetHeight()
	{
		//return this->frameHeight*this->scale.y;
		return this->height;
	}
	void SpriteAnimation::SetFrame(int frameIndex,bool isStopAnimation)
	{
		if (isStopAnimation) {
			this->isRunningAnimation = false;
		}
		if(frameIndex<numberOfFrame) this->srcRect = frameList[frameIndex];
		else g_debug.Warning("Frame index exceed number of frame.");
	}
	void SpriteAnimation::InitFrameList()
	{
		frameList = new RECT[numberOfFrame];
		RECT atlasRect = this->image->GetRect();
		for (int frameIndex = 0; frameIndex < this->numberOfFrame; frameIndex++) {
			RECT frame;
			int currentFrameRow = ((frameIndex) / this->framePerRow);
			int currentFrameColumn = (frameIndex - ((currentFrameRow)*this->framePerRow));
			int top = this->frameHeight*currentFrameRow;
			int left = this->frameWidth*currentFrameColumn;
			int right = left + this->frameWidth;
			int bottom = top + this->frameHeight;
			frame = { left,top,right,bottom };
			frame.left += atlasRect.left;
			frame.right += atlasRect.left;
			frame.top += atlasRect.top;
			frame.bottom += atlasRect.top;
			frameList[frameIndex] = frame;
		}
	}
	void SpriteAnimation::SetCurrentSrcRect()
	{
		int currentFrameRow = ((this->currentFrame) / this->framePerRow);
		int currentFrameColumn = (this->currentFrame - ((currentFrameRow)*this->framePerRow));
		int top = this->frameHeight*currentFrameRow;
		int left = this->frameWidth*currentFrameColumn;
		int right = left + this->frameWidth;
		int bottom = top + this->frameHeight;
		srcRect = { left,top,right,bottom };

		RECT atlasRect = this->image->GetRect();
		srcRect.left += atlasRect.left;
		srcRect.right += atlasRect.right;
		srcRect.top += atlasRect.top;
		srcRect.bottom += atlasRect.bottom;
	}
}