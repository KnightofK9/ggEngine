#pragma once
#include <ggEngine.h>
#include "TextureConstant.h"
using namespace ggEngine;
class CVPreload : public Preload {
public:
	CVPreload(Cache *cache);
	~CVPreload();
	void CharSimon();
	void UIInfoPanel();
	void FontGame();
};