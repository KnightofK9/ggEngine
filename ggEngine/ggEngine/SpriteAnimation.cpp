#include "SpriteAnimation.h"
#include "Animator.h"
namespace ggEngine {
	SpriteAnimation::SpriteAnimation(LPDIRECT3DDEVICE9 device, Texture * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame) :Sprite(device)
	{
		this->spriteAnimationType = SA_RectangleSheet;
		this->currentFrame = defaultFrame;
		this->isRunningAnimation = false;
		SetImage(image, frameWidth, frameHeight, numberOfFrame);
	}
	SpriteAnimation::~SpriteAnimation()
	{
		Destroy();
	}
	void SpriteAnimation::Draw()
	{
		Transform();
		RECT srcRect;
		if (this->isRunningAnimation && !this->currentAnimation->isFinished) this->isRunningAnimation = false;
		if (this->isRunningAnimation) {
			srcRect = this->currentAnimation->GetNextRect();
			this->currentFrame = this->currentAnimation->currentFrame;
		}
		else {
			int currentFrameRow = ((this->currentFrame) / this->framePerRow);
			int currentFrameColumn = (this->currentFrame - ((currentFrameRow)*this->framePerRow));
			srcRect = { currentFrameRow,currentFrameColumn,currentFrameRow + this->frameWidth, currentFrameColumn + this->frameHeight };
		}
		if (this->spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			this->spriteHandle->Draw(this->GetImage()->GetTexture(), &srcRect, NULL, NULL, D3DXCOLOR(255, 255, 255, 255));
			spriteHandle->End();
		}
	}
	void SpriteAnimation::Destroy()
	{
		for (std::map<std::string, Animator*>::iterator it = this->animatorMap.begin(); it != this->animatorMap.end(); ++it) {
			(it->second)->Destroy();
		};
	}
	void SpriteAnimation::CreateAnimation(std::string animationName, int startFrame, int endFrame, bool isLoop)
	{
		if (endFrame > this->numberOfFrame) {
			Debug::Warning("End frame is bigger than number of frame.");
			endFrame = this->numberOfFrame;
		}
		if (startFrame < 0) {
			Debug::Warning("Start frame must not be negative.");
			startFrame = 0;
		}
		animatorMap[animationName] = new Animator(startFrame, endFrame, this, isLoop);
	}
	void SpriteAnimation::PlayAnimation(std::string animationName)
	{
		std::map<std::string, Animator*>::iterator it = this->animatorMap.find(animationName);
		if (it != this->animatorMap.end())
		{
			this->currentAnimation = (it->second);
			this->isRunningAnimation = true;
		}
		else {
			Debug::Warning("No animation found  with key " + animationName);
		}
	}
	void SpriteAnimation::SetImage(Texture * image, int frameWidth, int frameHeight, int numberOfFrame)
	{
		this->image = image;
		this->frameHeight = frameHeight;
		this->frameWidth = frameWidth;
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
	void SpriteAnimation::SetWidth(int width)
	{
		this->scale.x = ((float)width / this->frameWidth);
		this->width = width;
	}
	void SpriteAnimation::SetHeight(int height)
	{
		this->scale.y = (float)height / this->frameHeight;
		this->height = height;
	}
	int SpriteAnimation::GetWidth()
	{
		return this->frameWidth*this->scale.x;
	}
	int SpriteAnimation::GetHeight()
	{
		return this->frameHeight*this->scale.y;
	}
}