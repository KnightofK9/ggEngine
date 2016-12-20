#include "CVCamera.h"
#include "CVBlock.h"
#include "Constant.h"
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
		double blockTop = block->top - floor(Constant::UI_INFO_PANEL_BACKGROUND_HEIGHT / this->scale.y);
		if (r.left < block->left)
			this->point.x += block->left - r.left;
		if (r.right > block->right)
			this->point.x -= r.right - block->right;
		if (r.top < blockTop)
			this->point.y += blockTop -  r.top ;
		if (r.bottom > block->bottom)
			this->point.y -= r.bottom - block->bottom ;
	}
}
