#include "CVPreload.h"

CVPreload::CVPreload(Cache * cache):Preload(cache)
{
}

CVPreload::~CVPreload()
{
}

void CVPreload::CharSimon()
{
	this->Texture(TextureConstant::SIMON_TEXTURE, TextureConstant::SIMON_TEXTURE_PATH);
}
