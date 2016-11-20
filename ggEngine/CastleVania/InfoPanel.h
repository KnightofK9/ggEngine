#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(DrawManager* drawManager);
	~InfoPanel();
	virtual void Draw() override;
private:
	
};