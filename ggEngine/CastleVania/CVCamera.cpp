#include "CVCamera.h"
#include "CVBlock.h"
CVCamera::CVCamera(Game * game, int width, int height, double x, double y, bool enableManualMove) : Camera(game,width,height,x,y,enableManualMove)
{
}

CVCamera::~CVCamera()
{
}

void CVCamera::SetBlock(CVBlock * block)
{
	this->block = block;
}

void CVCamera::Update()
{
	Camera::Update();
	if (this->block != nullptr) {
		Rect r = this->GetNormalRect();
		if (r.left < block->left)
			//r.left = block->left;
			this->point.x += block->left - r.left;
		if (r.right > block->right)
			//r.right = block->right;
			this->point.x -= r.right - block->right;
		//if (r.top < block->top)
		//	//r.top = block->top;
		//	this->point.y += block->top -  r.top ;
		//if (r.bottom > block->bottom)
		//	//r.bottom = block->bottom;
		//	this->point.y -= r.bottom - block->bottom ;
		/*this->point.x = (r.left + r.right) / 2.0;
		this->point.y = (r.top + r.bottom) / 2.0;*/
	}
}
