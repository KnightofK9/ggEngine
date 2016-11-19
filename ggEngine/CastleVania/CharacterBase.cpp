#include "CharacterBase.h"

CharacterBase::CharacterBase(DrawManager * drawManager, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):SpriteAnimation(drawManager,image,frameWidth,frameHeight,defaultFrame,numberOfFrame,msPerFrame)
{

}

CharacterBase::~CharacterBase()
{
}
