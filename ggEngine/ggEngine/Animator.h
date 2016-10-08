#pragma once
#include <d3d9.h>
#include "SpriteAnimation.h"
#include "GGObject.h"
namespace ggEngine {
	class Animator:public GGObject {
	public:
		Animator(int startFrame, int endFrame, SpriteAnimation *spriteAnimation, bool isLoop);
		~Animator();
		void Destroy();
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
	private:
		RECT *frameList;
	};
}