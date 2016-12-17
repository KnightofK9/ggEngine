#include "CVBlock.h"

CVBlock::CVBlock(double left, double top, double right, double bottom, std::string name) : Rect(left,top,right,bottom)
{
	this->name = name;
}

CVBlock::~CVBlock()
{
}
