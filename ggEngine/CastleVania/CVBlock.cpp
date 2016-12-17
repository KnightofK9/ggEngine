#include "CVBlock.h"

CVBlock::CVBlock(std::string json)
{
	Json blockJson(json);
	double x = blockJson["x"].GetDouble();
	double y = blockJson["y"].GetDouble();
	double width = blockJson["width"].GetDouble();
	double height = blockJson["height"].GetDouble();
	
	this->left = x;
	this->right = x + width;
	this->top = y;
	this->bottom = y + height;

	this->simonSpawnPosition = Vector(blockJson["simonPosition"]["x"].GetDouble(), blockJson["simonPosition"]["y"].GetDouble());
	this->cameraSpawnPosition = Vector(blockJson["cameraPosition"]["x"].GetDouble(), blockJson["cameraPosition"]["y"].GetDouble());
}

CVBlock::~CVBlock()
{
}
