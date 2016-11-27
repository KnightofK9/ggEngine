#include "CharacterBase.h"

CharacterBase::CharacterBase(CVGame *cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image,frameWidth,frameHeight,defaultFrame,numberOfFrame,msPerFrame)
{

}

CharacterBase::~CharacterBase()
{
}
