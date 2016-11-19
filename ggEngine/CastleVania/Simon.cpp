#include "Simon.h"

Simon::Simon(DrawManager * drawManager, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) : CharacterBase(drawManager, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->tag = ObjectType_Simon;
}

Simon::~Simon()
{
}
