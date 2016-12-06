#pragma once
#include <ggEngine.h>
#include "TextureConstant.h"

using namespace ggEngine;
class CVGame;
class CVPreload   {
public:
	CVPreload(CVGame *game);
	virtual ~CVPreload();
	void CharSimon();
	void UIInfoPanel();
	void FontGame();
private:
	Preload* preload = nullptr;
};