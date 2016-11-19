#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVState : public State {
public :
	CVState(Game *game);
	CVState(Game *game,Json state);
	~CVState();
	
	void Load() override;
protected:
	virtual void LoadJson(Json state);
};