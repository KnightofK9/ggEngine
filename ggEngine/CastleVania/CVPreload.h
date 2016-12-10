#pragma once
#include <ggEngine.h>
#include "TextureConstant.h"
#include "ManagerBase.h"
using namespace ggEngine;
class CVPreload  : ManagerBase {
public:
	CVPreload(CVGame *game);
	virtual ~CVPreload();
	void CharSimon();
	void UIInfoPanel();
	void FontGame();
private:
};